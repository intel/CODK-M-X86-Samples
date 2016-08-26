/*
Copyright (c) 2016 Intel Corporation.  All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#include <zephyr.h>

#include <device.h>
#include <spi.h>

#include "wiring_spi.h"
#include "arduino.h"

#include <pinmux.h>
#include <sys_io.h>

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

struct device *spi_dev;
struct spi_config spi1_config;

void spi1_setClockDivider(uint8_t clockDiv)
{
	spi1_config.max_sys_freq = clockDiv;
	spi_configure(spi_dev, &spi1_config);
}

void spi1_setDataMode(uint8_t dataMode)
{
	switch (dataMode)
	{
	case SPI_MODE0:
		spi1_config.config = (spi1_config.config & 0xFFFFFFF0);
		break;
	case SPI_MODE1:
		spi1_config.config = (spi1_config.config & 0xFFFFFFF0) | SPI_MODE_CPHA ;
		break;
	case SPI_MODE2:
		spi1_config.config = (spi1_config.config & 0xFFFFFFF0) | SPI_MODE_CPOL;
		break;
	case SPI_MODE3:
		spi1_config.config = (spi1_config.config & 0xFFFFFFF0) | SPI_MODE_CPOL | SPI_MODE_CPHA;
		break;
	default:
		spi1_config.config = (spi1_config.config & 0xFFFFFFF0);
		break;
	}
	spi_configure(spi_dev, &spi1_config);
}

void spi1_begin()
{
	spi_dev = device_get_binding("SPI_1");
	int err;
	
	spi1_config.config = SPI_MODE_CPOL | SPI_MODE_CPHA | SPI_WORD(16);
	spi1_config.max_sys_freq = SPI_CLOCK_DIV2;	//default 8Mhz

	err = spi_configure(spi_dev, &spi1_config);

	err = spi_slave_select(spi_dev, 1);
	
	//mux out the SPI pins for Arduino/Genuino 101
	struct device *p_mux = device_get_binding("PINMUX_DEV");

	pinmux_pin_set(p_mux, 0, PINMUX_FUNC_C);
	pinmux_pin_set(p_mux, 1, PINMUX_FUNC_C);
	pinmux_pin_set(p_mux, 2, PINMUX_FUNC_C);
	pinmux_pin_set(p_mux, 3, PINMUX_FUNC_C);
	pinmux_pin_set(p_mux, 42, PINMUX_FUNC_B);
	pinmux_pin_set(p_mux, 43, PINMUX_FUNC_B);
	pinmux_pin_set(p_mux, 44, PINMUX_FUNC_B);
	pinmux_pin_set(p_mux, 45, PINMUX_FUNC_B);
	 
}

void spi1_end()
{
	//return to default mux configuration
	struct device *p_mux = device_get_binding("PINMUX_DEV");
	
	pinmux_pin_set(p_mux, 0, PINMUX_FUNC_A);
	pinmux_pin_set(p_mux, 1, PINMUX_FUNC_A);
	pinmux_pin_set(p_mux, 2, PINMUX_FUNC_A);
	pinmux_pin_set(p_mux, 3, PINMUX_FUNC_A);
	pinmux_pin_set(p_mux, 42, PINMUX_FUNC_A);
	pinmux_pin_set(p_mux, 43, PINMUX_FUNC_A);
	pinmux_pin_set(p_mux, 44, PINMUX_FUNC_A);
	pinmux_pin_set(p_mux, 45, PINMUX_FUNC_A);
}

uint8_t spi1_transfer(uint8_t data)
{
	int err;
	uint8_t rx_buffer[1];
	uint8_t *buff = &data;

	spi1_config.config = (spi1_config.config & 0xFFFFF00F) | SPI_WORD(8);
	spi_configure(spi_dev, &spi1_config);
	
	err = spi_transceive(spi_dev, buff, sizeof(uint8_t),
			     rx_buffer, sizeof(rx_buffer));

	return *rx_buffer;
}

uint16_t spi1_transfer16(uint16_t data)
{
	int err;
	uint8_t rx_buffer[2];
	uint16_t *buff = &data;

	spi1_config.config = (spi1_config.config & 0xFFFFF00F) | SPI_WORD(16);
	spi_configure(spi_dev, &spi1_config);

	err = spi_transceive(spi_dev, buff, sizeof(uint16_t),
			     rx_buffer, sizeof(rx_buffer));

	uint16_t *rbuff;
	rbuff = (uint16_t*)rx_buffer;
	return *rbuff;
}

uint32_t spi1_transfer24(uint32_t data)
{
	int err;
	uint8_t rx_buffer[4];
	data = data & 0x00FFFFFF;
	uint32_t *buff = &data;

	spi1_config.config = (spi1_config.config & 0xFFFFF00F) | SPI_WORD(32);
	spi_configure(spi_dev, &spi1_config);

	err = spi_transceive(spi_dev, buff, sizeof(uint32_t),
			     rx_buffer, sizeof(rx_buffer));

	uint32_t *rbuff;
	rbuff = (uint32_t*)rx_buffer;
	return *rbuff;
}

uint32_t spi1_transfer32(uint32_t data)
{
	int err;
	uint8_t rx_buffer[4];
	uint32_t *buff = &data;

	spi1_config.config = (spi1_config.config & 0xFFFFF00F) | SPI_WORD(32);
	spi_configure(spi_dev, &spi1_config);

	err = spi_transceive(spi_dev, buff, sizeof(uint32_t),
			     rx_buffer, sizeof(rx_buffer));

	uint32_t *rbuff;
	rbuff = (uint32_t*)rx_buffer;
	return *rbuff;
}


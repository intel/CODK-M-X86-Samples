/*
 * Copyright (c) 2016 Intel Corporation.  All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#include "SPI_LIB.h"

#include <pinmux.h>
#include <sys_io.h>

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

SPIClass::SPIClass(int devID)
{
	dev_id = devID;
}

void SPIClass::begin()
{
	struct device *p_mux = device_get_binding((char*)"PINMUX_DEV");
	if(dev_id == 0)
	{
		spi_dev = device_get_binding((char*)"SPI_0");
		if (!spi_dev) {
			PRINT("SPI_0: Device not found.\n");
			return;
		}
		init_status = 1;
	
	}
	else
	{
		spi_dev = device_get_binding((char*)"SPI_1");
		if (!spi_dev) {
			PRINT("SPI_1: Device not found.\n");
			return;
		}
		pinmux_pin_set(p_mux, 0, PINMUX_FUNC_C);
		pinmux_pin_set(p_mux, 1, PINMUX_FUNC_C);
		pinmux_pin_set(p_mux, 2, PINMUX_FUNC_C);
		pinmux_pin_set(p_mux, 3, PINMUX_FUNC_C);
		pinmux_pin_set(p_mux, 42, PINMUX_FUNC_B);
		pinmux_pin_set(p_mux, 43, PINMUX_FUNC_B);
		pinmux_pin_set(p_mux, 44, PINMUX_FUNC_B);
		pinmux_pin_set(p_mux, 45, PINMUX_FUNC_B);
		init_status = 1;
	}

	spi_config.config = SPI_MODE_CPOL | SPI_MODE_CPHA | SPI_WORD(16);
	spi_config.max_sys_freq = SPI_CLOCK_DIV2;	//default 8Mhz

	spi_configure(spi_dev, &spi_config);
	spi_slave_select(spi_dev, 1);
}

void SPIClass::setClockDivider(uint8_t clockDiv)
{
	spi_config.max_sys_freq = clockDiv;
	spi_configure(spi_dev, &spi_config);
}

void SPIClass::setDataMode(uint8_t dataMode)
{
	switch (dataMode)
	{
	case SPI_MODE0:
		spi_config.config = (spi_config.config & 0xFFFFFFF0);
		break;
	case SPI_MODE1:
		spi_config.config = (spi_config.config & 0xFFFFFFF0) | SPI_MODE_CPHA ;
		break;
	case SPI_MODE2:
		spi_config.config = (spi_config.config & 0xFFFFFFF0) | SPI_MODE_CPOL;
		break;
	case SPI_MODE3:
		spi_config.config = (spi_config.config & 0xFFFFFFF0) | SPI_MODE_CPOL | SPI_MODE_CPHA;
		break;
	default:
		spi_config.config = (spi_config.config & 0xFFFFFFF0);
		break;
	}
	spi_configure(spi_dev, &spi_config);
}

void SPIClass::setSlaveSelect(int gpio)
{
	ss_gpio = gpio;
}

uint8_t SPIClass::transfer(uint8_t data)
{
	int err;
	uint8_t rx_buffer[1];
	uint8_t *buff = &data;

	spi_config.config = (spi_config.config & 0xFFFFF00F) | SPI_WORD(8);
	spi_configure(spi_dev, &spi_config);
	
	err = spi_transceive(spi_dev, buff, sizeof(uint8_t),
			     rx_buffer, sizeof(rx_buffer));

	return *rx_buffer;
}

uint16_t SPIClass::transfer16(uint16_t data)
{
	int err;
	uint8_t rx_buffer[2];
	uint16_t *buff = &data;

	spi_config.config = (spi_config.config & 0xFFFFF00F) | SPI_WORD(16);
	spi_configure(spi_dev, &spi_config);

	err = spi_transceive(spi_dev, buff, sizeof(uint16_t),
			     rx_buffer, sizeof(rx_buffer));

	uint16_t *rbuff;
	rbuff = (uint16_t*)rx_buffer;
	return *rbuff;
}

uint32_t SPIClass::transfer24(uint32_t data)
{
	int err;
	uint8_t rx_buffer[4];
	data = data & 0x00FFFFFF;
	uint32_t *buff = &data;

	spi_config.config = (spi_config.config & 0xFFFFF00F) | SPI_WORD(32);
	spi_configure(spi_dev, &spi_config);

	err = spi_transceive(spi_dev, buff, sizeof(uint32_t),
			     rx_buffer, sizeof(rx_buffer));

	uint32_t *rbuff;
	rbuff = (uint32_t*)rx_buffer;
	return *rbuff;
}

uint32_t SPIClass::transfer32(uint32_t data)
{
	int err;
	uint8_t rx_buffer[4];
	uint32_t *buff = &data;

	spi_config.config = (spi_config.config & 0xFFFFF00F) | SPI_WORD(32);
	spi_configure(spi_dev, &spi_config);

	err = spi_transceive(spi_dev, buff, sizeof(uint32_t),
			     rx_buffer, sizeof(rx_buffer));

	uint32_t *rbuff;
	rbuff = (uint32_t*)rx_buffer;
	return *rbuff;
}
// Preinstantiate Objects //////////////////////////////////////////////////////

SPIClass SPI0 = SPIClass(0);
SPIClass SPI1 = SPIClass(1);

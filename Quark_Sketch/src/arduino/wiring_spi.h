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

#include <stdint.h>
#include <device.h>

#ifndef _WIRING_SPI_
#define _WIRING_SPI_

#define SPI_CLOCK_DIV4     8	// 4 Mhz
#define SPI_CLOCK_DIV16   32	// 1 Mhz
#define SPI_CLOCK_DIV64  128	// 250 Khz
#define SPI_CLOCK_DIV128 256 	// 125 Khz
#define SPI_CLOCK_DIV2     4	// 8 Mhz
#define SPI_CLOCK_DIV1     2	// 16 Mhz
#define SPI_CLOCK_DIV8    16	// 2 Mhz
#define SPI_CLOCK_DIV32   64	// 500 Mhz

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

#ifdef __cplusplus
extern "C" {
#endif

void spi1_setClockDivider(uint8_t clockDiv);

void spi1_setDataMode(uint8_t dataMode);

void spi1_begin();

void spi1_end();

uint8_t spi1_transfer(uint8_t data);

uint16_t spi1_transfer16(uint16_t data);

uint32_t spi1_transfer24(uint32_t data);

uint32_t spi1_transfer32(uint32_t data);

void spi1_transfer_buff(void *buf, size_t count);

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_SPI_ */



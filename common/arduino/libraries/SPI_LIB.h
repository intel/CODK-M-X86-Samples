/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <zephyr.h>

#include <stdint.h>
#include <device.h>
#include <spi.h>

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#define SPI0_CS  21
#define SPI1_CS  SS

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

#define NUM_SPIDEVS 2

class SPIClass {
public:
	SPIClass(int devID);

	/* Initialize the SPI library */
	void begin();

	void setClockDivider(uint8_t clockDiv);

	void setDataMode(uint8_t dataMode);
	
	void setSlaveSelect(int gpio);

	uint8_t transfer(uint8_t data);

	uint16_t transfer16(uint16_t data);

	uint32_t transfer24(uint32_t data);

	uint32_t transfer32(uint32_t data);

	void transfer(void *buf, size_t count);

private:
	bool lsbFirst;
	uint8_t dev_id;
	struct device *spi_dev;
	struct spi_config spi_config;
	int init_status;
	int ss_gpio = 1;

};

extern SPIClass SPI0;
extern SPIClass SPI1;

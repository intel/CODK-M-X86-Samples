/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * Copyright (c) 2014 by Matthijs Kooijman <matthijs@stdin.nl> (SPISettings AVR)
 * Copyright (c) 2014 by Andrew J. Kroll <xxxajk@gmail.com> (atomicity fixes)
 * Copyright (c) 2016 by Intel Corporation <dino.tinitigan@intel.com (Curie ODK support)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
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

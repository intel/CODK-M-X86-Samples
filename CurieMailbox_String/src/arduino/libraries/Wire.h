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

#include <i2c.h>

#define BUFFER_LENGTH   32


class TwoWire {

public:
	TwoWire(int devID);
	void begin();
	void begin(int);
	void setClock(int speed);
	void beginTransmission(uint8_t);
	void beginTransmission(int);
	uint8_t endTransmission(void);
	uint8_t endTransmission(uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
	uint8_t requestFrom(int, int);
	uint8_t requestFrom(int, int, int);
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *, size_t);
	virtual int available(void);
	virtual int read(void);
	virtual int peek(void);
	virtual void flush(void);

private:
	// RX Buffer
	uint8_t rxBuffer[BUFFER_LENGTH];
	uint8_t rxBufferIndex;
	uint8_t rxBufferLength;

	// TX Buffer
	uint8_t txAddress;
	uint8_t txBuffer[BUFFER_LENGTH];
	uint8_t txBufferLength;

	uint8_t dev_id;
	struct device *i2c_dev;
	union dev_config cfg;
	int init_status;

	void i2c_setslave(uint8_t addr);
	int i2c_writebytes(uint8_t *bytes, uint8_t length, bool no_stop);
	int i2c_readbytes(uint8_t *buf, int length, bool no_stop);
};


extern TwoWire I2C0;
extern TwoWire I2C1;

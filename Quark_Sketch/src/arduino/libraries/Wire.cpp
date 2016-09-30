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

#include <device.h>
#include <i2c.h>

#include "Wire.h"

#include <pinmux.h>
#include <sys_io.h>

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

TwoWire::TwoWire(int devID)
{
	dev_id = devID;
}

void TwoWire::begin()
{
	struct device *p_mux = device_get_binding((char*)"PINMUX_DEV");

	if(dev_id == 0)
	{
		i2c_dev = device_get_binding((char*)"I2C_0");
		if (!i2c_dev) {
			PRINT("I2C_0: Device not found.\n");
			return;
		}
		pinmux_pin_set(p_mux, 20, PINMUX_FUNC_A);
		pinmux_pin_set(p_mux, 21, PINMUX_FUNC_A);
		init_status = 1;
	
	}
	else
	{
		i2c_dev = device_get_binding((char*)"I2C_1");
		if (!i2c_dev) {
			PRINT("I2C_1: Device not found.\n");
			return;
		}
		pinmux_pin_set(p_mux, 22, PINMUX_FUNC_A);
		pinmux_pin_set(p_mux, 23, PINMUX_FUNC_A);
		init_status = 1;
	}
	cfg.raw = 0;
	cfg.bits.use_10_bit_addr = 0;
	cfg.bits.speed = I2C_SPEED_STANDARD;
	cfg.bits.is_master_device = 1;

	if (i2c_configure(i2c_dev, cfg.raw) != 0) {
		PRINT("Error on i2c_configure()\n");
	}
}

//Valid values for speed
//I2C_SPEED_STANDARD 	100 KHz
//I2C_SPEED_FAST	400 KHz
void TwoWire::setClock(int speed)
{
	cfg.bits.speed = speed;
	if (i2c_configure(i2c_dev, cfg.raw) != 0) {
		PRINT("Error on i2c_configure()\n");
	}
}

void TwoWire::beginTransmission(uint8_t addr)
{
	if (init_status < 0)
		return;
	// set slave address
	i2c_setslave(addr);
	// reset transmit buffer
	tx_bufferLength = 0;
}

void TwoWire::beginTransmission(int addr)
{
	beginTransmission((uint8_t) addr);
}

uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
	int err;
		// transmit buffer (blocking)
	if (tx_bufferLength >= 1) {
		err = i2c_writebytes(tx_buffer, tx_bufferLength, !sendStop);
	} else {
		uint8_t temp = 0;
		// Workaround: I2C bus scan is currently implemented by reading,
		// so set the read length to 0 to inform the lower I2C driver that we are doing bus scan
		err = i2c_readbytes(&temp, 0, 0);
	}
	// empty buffer
	tx_bufferLength = 0;
	if (err < 0) {
		return -err;
	}
	return 0; // success
}

uint8_t TwoWire::endTransmission(void)
{
	return endTransmission(true);
}

uint8_t TwoWire::requestFrom(uint8_t addr, uint8_t quantity, uint8_t sendStop)
{
	if (quantity > BUFFER_LENGTH)
	{
		quantity = BUFFER_LENGTH;
	}
	i2c_setslave(addr);
	int ret = i2c_readbytes(rx_buffer, quantity, !sendStop);
	if (ret < 0)
	{
		return 0;
	}

	// set rx buffer index back to 0
	rx_bufferIndex = 0;
	rx_bufferLength = quantity;

	return quantity;
}

uint8_t TwoWire::requestFrom(uint8_t addr, uint8_t quantity)
{
	return requestFrom((uint8_t)addr, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int addr, int quantity, int sendStop)
{
	return requestFrom((uint8_t)addr, (uint8_t)quantity, (uint8_t)sendStop);
}

uint8_t TwoWire::requestFrom(int addr, int quantity)
{
	return requestFrom((uint8_t)addr, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::write(uint8_t data)
{
	if (tx_bufferLength >= BUFFER_LENGTH)
	{
		return 0;
	}
	tx_buffer[tx_bufferLength++] = data;
	return 1;
}

uint8_t TwoWire::write(const uint8_t *data, uint8_t length)
{
	for (uint8_t i = 0; i < length; ++i) {
		if (tx_bufferLength >= BUFFER_LENGTH)
		{
			return i;
		}
		tx_buffer[tx_bufferLength++] = data[i];
	}
	return length;
}

int TwoWire::available()
{
	return rx_bufferLength - rx_bufferIndex;
}

uint8_t TwoWire::read()
{
	if (rx_bufferIndex < rx_bufferLength)
	{
		return rx_buffer[rx_bufferIndex++];
	}
	return -1;
}

uint8_t TwoWire::peek()
{
	if (rx_bufferIndex < rx_bufferLength)
	{
		return rx_buffer[rx_bufferIndex];
	}
	return -1;
}

void TwoWire::flush()
{
	//do nothing
}

void TwoWire::i2c_setslave(uint8_t addr)
{
	txAddress = addr;
}

int TwoWire::i2c_writebytes(uint8_t *bytes, uint8_t length, bool no_stop)
{
	struct i2c_msg msgs[1];

	int flags = 0;
	if(!no_stop)
	{
		flags = I2C_MSG_WRITE | I2C_MSG_STOP;
	}
	else
	{
		flags = I2C_MSG_WRITE;
	}	

	msgs[0].buf = bytes;
	msgs[0].len = length;
	msgs[0].flags = flags;
	
	return i2c_transfer(i2c_dev, &msgs[0], 1, txAddress);
}

int TwoWire::i2c_readbytes(uint8_t *buf, int length, bool no_stop)
{
	struct i2c_msg msgs[1];

	int flags = 0;
	if(!no_stop)
	{
		flags = I2C_MSG_READ | I2C_MSG_STOP;
	}
	else
	{
		flags = I2C_MSG_READ;
	}

	msgs[0].buf = buf;
	msgs[0].len = length;
	msgs[0].flags = flags;

	return i2c_transfer(i2c_dev, &msgs[0], 1, txAddress);
}

TwoWire I2C0 = TwoWire(0);
TwoWire I2C1 = TwoWire(1);

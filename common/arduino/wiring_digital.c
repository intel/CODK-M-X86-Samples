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

#include "wiring_digital.h"
#include "arduino.h"

#include <zephyr.h>

#include <misc/printk.h>

#include <device.h>
#include <gpio.h>
#include <misc/util.h>

#include <pinmux.h>

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

//#define GPIO_DRV_NAME CONFIG_GPIO_QMSI_0_NAME
#if defined(CONFIG_GPIO_DW_0)
#define GPIO_DRV_NAME CONFIG_GPIO_DW_0_NAME
#elif defined(CONFIG_GPIO_QMSI_0)
#define GPIO_DRV_NAME CONFIG_GPIO_QMSI_0_NAME
#elif defined(CONFIG_GPIO_ATMEL_SAM3)
#define GPIO_DRV_NAME CONFIG_GPIO_ATMEL_SAM3_PORTB_DEV_NAME
#else
#error "Unsupported GPIO driver"
#endif

#define PULL_UP 1
#define PINMUX_NAME CONFIG_PINMUX_NAME

struct device *gpio_dev;

void digitalInit()
{
	gpio_dev= device_get_binding(GPIO_DRV_NAME);
}

void pinMode(uint8_t pin, uint8_t mode)
{
	struct device *p_mux = device_get_binding(PINMUX_NAME);
	pinmux_pin_set(p_mux, zephyrDescription[pin].pinMux, zephyrDescription[pin].muxMode); //set to default gpio mux mode

	if(zephyrDescription[pin].zephyrPin2 != INVALID) 
	{
		gpio_pin_configure(gpio_dev, zephyrDescription[pin].zephyrPin2, (GPIO_DIR_IN)); //HIGH-Z
	}

	if(mode == OUTPUT)
	{
		gpio_pin_configure(gpio_dev, zephyrDescription[pin].zephyrPin1, (GPIO_DIR_OUT));
	}
	else if(mode == INPUT)
	{
		gpio_pin_configure(gpio_dev, zephyrDescription[pin].zephyrPin1, (GPIO_DIR_IN));
	}
	else if(mode == INPUT_PULLUP)
	{
		gpio_pin_configure(gpio_dev, zephyrDescription[pin].zephyrPin1, (GPIO_DIR_IN | PULL_UP));
	}
}

void digitalWrite(uint8_t pin, uint8_t level)
{
	gpio_pin_write(gpio_dev, zephyrDescription[pin].zephyrPin1, level);
}

int digitalRead(uint8_t pin)
{
	int ret = 0;
	gpio_pin_read(gpio_dev, zephyrDescription[pin].zephyrPin1, &ret);
	return ret;
}



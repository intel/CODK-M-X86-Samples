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

#include "wiring_analog.h"
#include "arduino.h"

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

#include <pwm.h>
#include <device.h>
#include <misc/byteorder.h>
#include <sys_clock.h>

#include <pinmux.h>

#define PWM_PERIOD 	2040	//490 Hz
#define HW_CLOCK_CYCLES_PER_USEC  (CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC / \
				   USEC_PER_SEC)
#ifdef __cplusplus
extern "C" {
#endif

/* Standard Arduino PWM resolution */
static int _writeResolution = 8;
uint32_t maxResolutionValue = 0xFF;

int pwm_period[4];

struct device *pwm_dev;

void analogInit()
{
	pwm_dev = device_get_binding("PWM_0");
	
	pwm_period[0] = PWM_PERIOD;
	pwm_period[1] = PWM_PERIOD/2;
	pwm_period[2] = PWM_PERIOD/2;
	pwm_period[3] = PWM_PERIOD;
	
}

void analogWriteResolution(int res)
{
	_writeResolution = res;
	maxResolutionValue = 0xFFFFFFFF >> (32-res);
}

static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to)
{
     if (from == to)
         return value;
     if (from > to)
         return value >> (from-to);
     else
         return value << (to-from);
}

void analogWrite(uint8_t pin, int val)
{
	pinMode(pin, OUTPUT);

	pwm_pin_set_period(pwm_dev, zephyrDescription[pin].pwmChannel, 
		pwm_period[zephyrDescription[pin].pwmChannel]);
	pwm_pin_set_values(pwm_dev, zephyrDescription[pin].pwmChannel, 0,
		(int)((pwm_period[zephyrDescription[pin].pwmChannel]* HW_CLOCK_CYCLES_PER_USEC) 
		* (val/(float)maxResolutionValue)));
}

void analogWriteFrequency(int pin, uint32_t frequency)
{
	uint32_t period = 1000000 / frequency;
	pwm_period[zephyrDescription[pin].pwmChannel] = period;
	
}

#ifdef __cplusplus
}
#endif

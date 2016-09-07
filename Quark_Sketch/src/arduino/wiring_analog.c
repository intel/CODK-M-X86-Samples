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

#include <pinmux.h>

#define PWM_PERIOD 	65306	//490 Hz
#define F_CPU 		32000000

#ifdef __cplusplus
extern "C" {
#endif

/* Standard Arduino PWM resolution */
static int _writeResolution = 8;

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

	int highPeriod = (val/255.0) * pwm_period[zephyrDescription[pin].pwmChannel];
	int lowPeriod = pwm_period[zephyrDescription[pin].pwmChannel] - highPeriod;
	pwm_pin_set_values(pwm_dev, zephyrDescription[pin].pwmChannel, highPeriod, lowPeriod);
}

void analogWriteFrequency(int pin, uint32_t frequency)
{
	uint32_t period = F_CPU / frequency;
	pwm_period[zephyrDescription[pin].pwmChannel] = period;
	
}

#ifdef __cplusplus
}
#endif

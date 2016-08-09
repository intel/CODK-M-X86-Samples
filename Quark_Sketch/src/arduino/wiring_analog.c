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

#define SLEEPTIME  2
#define SLEEPTICKS (SLEEPTIME * sys_clock_ticks_per_sec)


#ifdef __cplusplus
extern "C" {
#endif

/* Standard Arduino PWM resolution */
static int _writeResolution = 8;
static int _readResolution = 10;

struct device *pwm_dev;

#define PWM_PERIOD 32653	//490 Hz


void analogInit()
{
	pwm_dev = device_get_binding("PWM_0");
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
	PRINT("Analog Write\r\n");
	pinMode(pin, OUTPUT);

	int highPeriod = (val/255.0) * PWM_PERIOD*2;
	int lowPeriod = PWM_PERIOD*2 - highPeriod;
	pwm_pin_set_values(pwm_dev, zephyrDescription[pin].pwmChannel, highPeriod, lowPeriod);
}


#ifdef __cplusplus
}
#endif

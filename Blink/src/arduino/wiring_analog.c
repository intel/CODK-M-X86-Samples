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
#include <adc.h>

#include <pinmux.h>

#define ADC_DEVICE_NAME "ADC_0"
#define CHANNEL 10
#define BUFFER_SIZE 40

#define SLEEPTIME  2
#define SLEEPTICKS (SLEEPTIME * sys_clock_ticks_per_sec)

static uint8_t seq_buffer[BUFFER_SIZE];

static struct adc_seq_entry sample = {
	.sampling_delay = 12,
	.channel_id = CHANNEL,
	.buffer = seq_buffer,
	.buffer_length = BUFFER_SIZE,
};

static struct adc_seq_table table = {
	.entries = &sample,
	.num_entries = 1,
};

static void _print_sample_in_hex(uint8_t *buf, uint32_t length)
{
	PRINT("Buffer content:\n");
	for (; length > 0; length -= 4, buf += 4) {
		PRINT("0x%x ", *((uint32_t *)buf));
	}
	PRINT("\n");
}

#ifdef __cplusplus
extern "C" {
#endif

/* Standard Arduino PWM resolution */
static int _writeResolution = 8;
static int _readResolution = 10;

struct device *pwm_dev;
struct device *adc;

#define PWM_PERIOD 32653	//490 Hz


void analogInit()
{
	pwm_dev = device_get_binding("PWM_0");
	adc = device_get_binding(ADC_DEVICE_NAME);
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

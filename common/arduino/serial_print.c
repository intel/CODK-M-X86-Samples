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

#include "serial_print.h"
#include "arduino.h"


#include <zephyr.h>
#include "arduino101_services/curie_shared_mem.h"
#include <string.h>

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif


int serial_print(const char *buf)
{
	if(!serial_host_isopen() || !serial_device_isopen())
		return 0;
	int size = strlen(buf);
	for(int i = 0; i < size; i++)
	{
		serial_write(buf[i]);
		
	}
	return 1;
}

int serial_println(const char *buf)
{
	if(!serial_host_isopen() || !serial_device_isopen())
		return 0;
	int size = strlen(buf);
	for(int i = 0; i < size; i++)
	{
		serial_write(buf[i]);
		
	}
	serial_write('\r');
	serial_write('\n');
	return 1;
}

int serial_printInt(int val)
{
	if(!serial_host_isopen() || !serial_device_isopen())
		return 0;
	char buf[12];
	memset(buf, '\0', 12);
	int digits = 0;
	int n = val;
	while(n > 0)
	{
		digits++;
		n /= 10;
	}
	
	sprintf(buf, "%d", val);
	serial_print(buf);
	return 1;
}

int serial_printFloat(float f, int digits)
{
	if(!serial_host_isopen() || !serial_device_isopen())
		return 0;
	char buf[32];
	memset(buf, '\0', 32);
	if(f > 0)
		digits += 2;	//add 2 for the decimal point and \0
	else	
		digits += 3;	//add 2 for decimal point, minus sign, and \0
	PRINT("digits: %d\r\n", digits);
	snprintf(buf, digits, "%f", f);
	serial_print(buf);
	return 1;
}

int serial_printChar(char c)
{
	if(!serial_host_isopen() || !serial_device_isopen())
		return 0;
	serial_write((uint8_t)c);
	return 1;
	
}

int serial_write(const uint8_t uc_data)
{
	int new_head = (uint16_t)(Tx_HEAD + 1) % SBS;
	if(new_head != Tx_TAIL)
	{
		Tx_BUFF[Tx_HEAD] = uc_data;
		Tx_HEAD = new_head;
		return 1;
	}
	else
		return 0;
}

uint16_t serial_available()
{
	if(!serial_device_isopen())
		return 0;
	else
		return (uint16_t)(SBS + Rx_HEAD - Rx_TAIL)%SBS;
}

uint16_t serial_availableForWrite()
{
	if(!serial_host_isopen() || !serial_device_isopen())
		return 0;

	int head = Tx_HEAD;
	int tail = Tx_TAIL;

	if(head >= tail)
		return SBS - head + tail - 1;
	return tail - head - 1;
}

int serial_peek()
{
	if(!serial_host_isopen() || (Rx_HEAD == Rx_TAIL))
		return -1;

	return Rx_BUFF[Rx_TAIL];
}

int serial_read()
{
	if(!serial_host_isopen() || (Rx_HEAD == Rx_TAIL))
		return -1;

	uint8_t uc = Rx_BUFF[Rx_TAIL];
	Rx_TAIL = (Rx_TAIL + 1)%SBS;
	return uc;
}

void serial_flush()
{
	while(Tx_TAIL != Tx_HEAD)
	{
		delayMicroseconds(1);
	}
}

int serial_device_isopen()
{
	return curie_shared_data->cdc_acm_buffers_obj.device_open;
}

int serial_host_isopen()
{
	return curie_shared_data->cdc_acm_buffers_obj.host_open;
}


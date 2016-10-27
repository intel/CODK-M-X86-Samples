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
#include "arduino/arduino.h"
#include "arduino101_services/sharedmemory_com.h"

void main (void)
{
	//setup

	//loop
	while(1)
	{
		for(int i = 0; i < smc_availableForRead(); i++)
		{
			smc_write(smc_read() * 2);
		}
		task_yield();
	}
}

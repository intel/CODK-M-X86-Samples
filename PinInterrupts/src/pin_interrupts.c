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
#include "arduino101_services/arduino101_services.h"

void togglePin();

void main (void)
{
    // Required for Arduino-like functionality on x86
    variantInit();

	//setup
	pinMode(12, INPUT);
	attachInterrupt(12, togglePin, FALLING);
	//loop
	while(1)
	{
		task_yield();
	}
}

void togglePin()
{
	pinMode(13,OUTPUT);
	digitalWrite(13, HIGH);
	digitalWrite(13, LOW);
}

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

void main (void)
{
	//based on the Fade.ino example from Arduino

	//setup
	int led = 6;           // the PWM pin the LED is attached to
	int brightness = 0;    // how bright the LED is
	int fadeAmount = 5;    // how many points to fade the LED by

	analogWriteFrequency(led, 20000); //set frequency to 20 KHz

	//loop
	while(1)
	{
		analogWrite(led, brightness);

		// change the brightness for next time through the loop:
		brightness = brightness + fadeAmount;

		// reverse the direction of the fading at the ends of the fade:
		if (brightness <= 0 || brightness >= 255) {
		  fadeAmount = -fadeAmount;
		}
		// wait for 30 milliseconds to see the dimming effect
		delay(30);
		task_yield();
	}
}

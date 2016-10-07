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

#ifndef Arduino_h
#define Arduino_h


#include "variant.h"
#include "wiring_digital.h"
#include "wiring_analog.h"
#include "WInterrupts.h"
#include "wiring.h"
#include "serial_print.h"

#define LOW  0x00
#define HIGH 0x01
#define CHANGE 0x02
#define FALLING 0x03
#define RISING 0x04

#define INPUT 0x0
#define OUTPUT 0x01
#define INPUT_PULLUP 0x02

#define INVALID 255
#define SS_GPIO	0x00
#define SOC_GPIO 0x01

#ifdef __cplusplus
extern "C" {
#endif

void setup( void );
void loop( void );

typedef struct _ZephyrPinDescription
{
	uint8_t zephyrPin1;
	uint8_t zephyrPin2;
	uint8_t pinMux;
	uint8_t muxMode;
	uint8_t pwmChannel;
	uint8_t pinMode;
	uint8_t fabric;
} ZephyrPinDescription;

extern ZephyrPinDescription zephyrDescription[];

#ifdef __cplusplus
}
#endif



#endif // Arduino_h

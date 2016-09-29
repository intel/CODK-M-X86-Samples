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

#ifndef _WIRING_INTERRUPTS_
#define _WIRING_INTERRUPTS_

#include "arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

void attachInterrupt(uint32_t pin, void (*callback)(void), uint32_t mode);

void detachInterrupt(uint32_t pin);

void interrupts(void);

void noInterrupts(void);

#ifdef __cplusplus
}
#endif

#endif

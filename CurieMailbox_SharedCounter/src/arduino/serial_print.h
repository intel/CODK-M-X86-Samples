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

#ifndef SERIAL_PRINT_H
#define SERIAL_PRINT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int serial_print(const char *buf);

int serial_println(const char *buf);

int serial_printInt(int val);

int serial_printFloat(float f, int digits);

int serial_printChar(char c);

int serial_write(const uint8_t uc_data);

uint16_t serial_available();

uint16_t serial_availableForWrite();

int serial_peek();

int serial_read();

void serial_flush();

int serial_device_isopen();

int serial_host_isopen();

#ifdef __cplusplus
}
#endif


#endif //SERIAL_PRINT_H


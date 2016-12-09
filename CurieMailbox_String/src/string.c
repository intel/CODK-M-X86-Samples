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
#include <ipm.h>
#include <ipm/ipm_quark_se.h>
#include "arduino101_services/arduino101_services.h"

#define SLEEP_TIME 100

/* Sending messages on all 8 channels */
QUARK_SE_IPM_DEFINE(ipm0, 0, QUARK_SE_IPM_OUTBOUND);
QUARK_SE_IPM_DEFINE(ipm1, 1, QUARK_SE_IPM_OUTBOUND);
QUARK_SE_IPM_DEFINE(ipm2, 2, QUARK_SE_IPM_OUTBOUND);
QUARK_SE_IPM_DEFINE(ipm3, 3, QUARK_SE_IPM_OUTBOUND);
QUARK_SE_IPM_DEFINE(ipm4, 4, QUARK_SE_IPM_OUTBOUND);
QUARK_SE_IPM_DEFINE(ipm5, 5, QUARK_SE_IPM_OUTBOUND);
QUARK_SE_IPM_DEFINE(ipm6, 6, QUARK_SE_IPM_OUTBOUND);
QUARK_SE_IPM_DEFINE(ipm7, 7, QUARK_SE_IPM_OUTBOUND);

const char data0[] = "Mailbox";
const char data1[] = "greetings";
const char data2[] = "from";
const char data3[] = "the";
const char data4[] = "Arduino";
const char data5[] = "101";
const char data6[] = "x86";
const char data7[] = "core!\n";

void main (void)
{
    struct device *ipm0 = device_get_binding("ipm0");
    struct device *ipm1 = device_get_binding("ipm1");
    struct device *ipm2 = device_get_binding("ipm2");
    struct device *ipm3 = device_get_binding("ipm3");
    struct device *ipm4 = device_get_binding("ipm4");
    struct device *ipm5 = device_get_binding("ipm5");
    struct device *ipm6 = device_get_binding("ipm6");
    struct device *ipm7 = device_get_binding("ipm7");

    while (1) {
        task_sleep(SLEEP_TIME);
        ipm_send(ipm0, 1, 0, data0, 8);
        ipm_send(ipm1, 1, 0, data1, 9);
        ipm_send(ipm2, 1, 0, data2, 5);
        ipm_send(ipm3, 1, 0, data3, 4);
        ipm_send(ipm4, 1, 0, data4, 8);
        ipm_send(ipm5, 1, 0, data5, 4);
        ipm_send(ipm6, 1, 0, data6, 4);
        ipm_send(ipm7, 1, 0, data7, 7);
        task_yield();
    }
}

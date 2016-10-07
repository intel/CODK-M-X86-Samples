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

/* Sending messages on channel 1 */
QUARK_SE_IPM_DEFINE(ipm_send, 1, QUARK_SE_IPM_OUTBOUND);

/* Receiving messages on channel 0 */
QUARK_SE_IPM_DEFINE(ipm_receive, 0, QUARK_SE_IPM_INBOUND);

static struct device *ipm;
static struct device *rec_ipm;
static volatile uint32_t val;
static volatile bool received;

void ipm_callback(void *context, uint32_t id, volatile void *data)
{
	uint32_t *udata = (uint32_t *)data;
    val = *udata + 1;
    received = true;
}

void main (void)
{
    received = false;
    ipm = device_get_binding("ipm_send");
	rec_ipm = device_get_binding("ipm_receive");
	ipm_register_callback(rec_ipm, ipm_callback, NULL);
	ipm_set_enabled(rec_ipm, 1);

    while (1) {
        if (received) {
            received = false;
            ipm_send(ipm, 1, 0, (uint32_t *)&val, sizeof(uint32_t));
        }

        task_yield();
    }
}

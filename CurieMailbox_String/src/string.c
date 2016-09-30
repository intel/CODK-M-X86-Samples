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


#include <stdio.h>
#include <device.h>
#include <zephyr.h>
#include <gpio.h>
#include <ipm.h>
#include <ipm/ipm_quark_se.h>
#include "soc.h"

#include "arduino/arduino.h"
#include "sharedmemory_com.h"
#include "soc_ctrl.h"
#include "cdcacm_serial.h"
#include "curie_shared_mem.h"

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

#define SLEEP_TIME 100
#define SOFTRESET_INTERRUPT_PIN 0


/* Sending messages on channel 0 */
QUARK_SE_IPM_DEFINE(ipm_send, 0, QUARK_SE_IPM_OUTBOUND);

const char data[] = "Hello from x86";

struct gpio_callback cb;

void softResetButton();

static void softReset_button_callback(struct device *port, struct gpio_callback *cb, uint32_t pins)
{
    soft_reboot();
}

void main(void)
{
    init_cdc_acm();
    softResetButton();
    init_sharedMemory_com();

    // start ARC core
    uint32_t *reset_vector;
    reset_vector = (uint32_t *)RESET_VECTOR;
    start_arc(*reset_vector);

    task_start(QUARK_SKETCH);
    task_start(CDCACM_SETUP);
    task_start(BAUDRATE_RESET);
    task_start(USB_SERIAL);
}


void quark_sketch(void)
{
    struct device *ipm = device_get_binding("ipm_send");

    while (1) {
        task_sleep(SLEEP_TIME);
        ipm_send(ipm, 1, 0, data, 16);
        task_yield();
    }
}

void softResetButton()
{
    struct device *aon_gpio;
    char* gpio_aon_0 = (char*)"GPIO_AON_0";
    aon_gpio = device_get_binding(gpio_aon_0);
    if (!aon_gpio) 
    {
        return;
    }

    gpio_init_callback(&cb, softReset_button_callback, BIT(SOFTRESET_INTERRUPT_PIN));
    gpio_add_callback(aon_gpio, &cb);

    gpio_pin_configure(aon_gpio, SOFTRESET_INTERRUPT_PIN,
               GPIO_DIR_IN | GPIO_INT | GPIO_INT_EDGE |
               GPIO_INT_ACTIVE_LOW | GPIO_INT_DEBOUNCE);

    gpio_pin_enable_callback(aon_gpio, SOFTRESET_INTERRUPT_PIN);
}

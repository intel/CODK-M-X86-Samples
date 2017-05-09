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

#include "arduino.h"

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

#define PINMUX_NAME CONFIG_PINMUX_NAME



#ifdef __cplusplus
extern "C" {
#endif

//X86 pin mapping
ZephyrPinDescription zephyrDescription[]=
{

//	zephyrPin1, zephyrPin2, pinMux, muxMode,	pwmChannel, pinMode, fabric
	{9,	    INVALID,	17,	PINMUX_FUNC_C,	INVALID,    INPUT,   SS_GPIO}, // Arduino IO0
	{8,	    INVALID, 	16, 	PINMUX_FUNC_C,	INVALID,    INPUT,   SS_GPIO}, // Arduino IO1
	{18,	    INVALID, 	52, 	GPIO_MUX_MODE,	INVALID,    INPUT,   SOC_GPIO}, // Arduino IO2
	{17,	    INVALID, 	63, 	PWM_MUX_MODE,	0, 	    INPUT,   SOC_GPIO}, // Arduino IO3
	{19, 	    INVALID, 	53, 	GPIO_MUX_MODE,	INVALID,    INPUT,   SOC_GPIO}, // Arduino IO4
	{15, 	    INVALID, 	64, 	PWM_MUX_MODE,	1, 	    INPUT,   SOC_GPIO}, // Arduino IO5
	{12, 	    INVALID, 	65, 	PWM_MUX_MODE,	2, 	    INPUT,   SS_GPIO}, // Arduino IO6
	{20, 	    INVALID, 	54, 	GPIO_MUX_MODE,	INVALID,    INPUT,   SOC_GPIO}, // Arduino IO7
	{16, 	    INVALID, 	50, 	GPIO_MUX_MODE,	INVALID,    INPUT,   SOC_GPIO}, // Arduino IO8
	{13, 	    66, 	66, 	PWM_MUX_MODE,	3, 	    INPUT,   SS_GPIO}, // Arduino IO9
	{11, 	    0, 		45, 	GPIO_MUX_MODE,	INVALID,    INPUT,   SOC_GPIO}, // Arduino IO10
	{10, 	    3, 		44, 	GPIO_MUX_MODE,	INVALID,    INPUT,   SOC_GPIO}, // Arduino IO11
	{9, 	    1, 		43, 	GPIO_MUX_MODE,	INVALID,    INPUT,   SOC_GPIO}, // Arduino IO12
	{8, 	    2, 		42, 	GPIO_MUX_MODE,	INVALID,    INPUT,   SOC_GPIO}, // Arduino IO13
	{2, 	    INVALID, 	10, 	INVALID,	INVALID,    INPUT,   SS_GPIO}, // Arduino IO14
	{3, 	    INVALID, 	11, 	INVALID,	INVALID,    INPUT,   SS_GPIO}, // Arduino IO15
	{4, 	    INVALID, 	12, 	INVALID,	INVALID,    INPUT,   SS_GPIO}, // Arduino IO16
	{5, 	    INVALID, 	13, 	INVALID,	INVALID,    INPUT,   SS_GPIO}, // Arduino IO17
	{6, 	    INVALID, 	14, 	I2C_MUX_MODE,	INVALID,    INPUT,   SS_GPIO}, // Arduino IO18
	{1, 	    INVALID, 	9, 	I2C_MUX_MODE,	INVALID,    INPUT,   SS_GPIO}, // Arduino IO19
	{0, 	    INVALID, 	8, 	INVALID,	INVALID,    INPUT,   SS_GPIO}, // Arduino IO20
	{24, 	    INVALID, 	58, 	GPIO_MUX_MODE,	INVALID,    INPUT,   SOC_GPIO}, // Arduino IO21
};

void variantInit()
{
	analogInit();
	digitalInit();
	
	struct device *p_mux = device_get_binding(PINMUX_NAME);
	for(int i = 0; i < NUM_DIGITAL_PINS; i++)
	{
		if(zephyrDescription[i].muxMode != INVALID)
		{
			pinmux_pin_set(p_mux, zephyrDescription[i].pinMux, zephyrDescription[i].muxMode);
		}
	}
}


#ifdef __cplusplus
}
#endif

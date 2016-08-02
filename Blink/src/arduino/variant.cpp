#include "arduino.h"

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif



#ifdef __cplusplus
extern "C" {
#endif

//X86 pin mapping
ZephyrPinDescription zephyrDescription[]=
{

//	arduinoPin, zephyrPin1, zephyrPin2, analogPinNumber, pwmChannel, pinMode, fabric
	{0,	INVALID, INVALID, INVALID, INVALID, INPUT, SS_GPIO},
	{1, 	INVALID, INVALID, INVALID, INVALID, INPUT, SS_GPIO},
	{2,	18, INVALID, INVALID, INVALID, INPUT, SOC_GPIO},
	{3,	17, 63, INVALID, 0, INPUT, SOC_GPIO},
	{4,	19, INVALID, INVALID, INVALID, INPUT, SOC_GPIO},
	{5,	15, 64, INVALID, 1, INPUT, SOC_GPIO},
	{6,	INVALID, 65, INVALID, 2, INPUT, SS_GPIO},
	{7,	20, INVALID, INVALID, INVALID, INPUT, SOC_GPIO},
	{8,	16, INVALID, INVALID, INVALID, INPUT, SOC_GPIO},
	{9,	INVALID, 66, INVALID, 3, INPUT, SS_GPIO},
	{10,	11, 0, INVALID, INVALID, INPUT, SOC_GPIO},
	{11,	10, 3, INVALID, INVALID, INPUT, SOC_GPIO},
	{12,	9, 1, INVALID, INVALID, INPUT, SOC_GPIO},
	{13,	8, 2, INVALID, INVALID, INPUT, SOC_GPIO},
	{14,	INVALID, INVALID, 10, INVALID, INPUT, SS_GPIO},
	{15,	INVALID, INVALID, 11, INVALID, INPUT, SS_GPIO},
	{16,	INVALID, INVALID, 13, INVALID, INPUT, SS_GPIO},
	{17,	INVALID, INVALID, 14, INVALID, INPUT, SS_GPIO},
	{18,	INVALID, INVALID, 14, INVALID, INPUT, SS_GPIO},
	{19,	INVALID, INVALID, 9, INVALID, INPUT, SS_GPIO},
	{20,	INVALID, INVALID, INVALID, INVALID, INPUT, SS_GPIO},
	{21,	24, INVALID, INVALID, INVALID, INPUT, SOC_GPIO},
};

void variantInit()
{
	analogInit();
	digitalInit();
}


#ifdef __cplusplus
}
#endif

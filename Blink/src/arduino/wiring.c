#include "wiring.h"
#include "arduino.h"

#include <zephyr.h>

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

void delay(uint32_t msecs)
{
	task_sleep(MSEC(msecs));
}

void delayMicroseconds(uint32_t msecs)
{
	task_sleep(USEC(msecs));
}


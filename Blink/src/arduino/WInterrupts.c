
#include "WInterrupts.h"
#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <misc/util.h>

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

/* change this to use another GPIO port */
#define PORT	"GPIOC"
/* change this to enable pull-up/pull-down */
#define PULL_UP 0
/* change this to use a different interrupt trigger */
#define EDGE    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)

static struct gpio_callback gpio_cb;

void attachInterrupt(uint32_t pin, void(*callback)(void), uint32_t mode)
{
	struct device *gpiob;
	gpiob = device_get_binding(PORT);

	gpio_pin_configure(gpiob, zephyrDescription[pin].zephyrPin1,
			GPIO_DIR_IN | GPIO_INT
			| EDGE
			| PULL_UP);

	gpio_init_callback(&gpio_cb, callback, zephyrDescription[pin].zephyrPin1);

}

void detachInterrupt(uint32_t pin)
{
}

void interrupts(void)
{
}

void noInterrupts(void)
{
}

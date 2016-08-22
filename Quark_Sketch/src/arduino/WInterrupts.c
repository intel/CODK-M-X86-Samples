#include "WInterrupts.h"
#include "arduino.h"

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
#define PORT	"GPIO_0"
/* change this to enable pull-up/pull-down */
#define PULL_UP 0
/* change this to use a different interrupt trigger */
#define EDGE    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)

static struct gpio_callback gpio_cb;

void attachInterrupt(uint32_t pin, void(*callback)(void), uint32_t mode)
{
	struct device *gpiob;
	int gpio_mode;
	switch(mode)
	{
	case LOW:
		gpio_mode = GPIO_DIR_IN | GPIO_INT
			| GPIO_INT_LEVEL | GPIO_INT_ACTIVE_LOW
			| PULL_UP;
		break;
	case HIGH:
		gpio_mode = GPIO_DIR_IN | GPIO_INT
			| GPIO_INT_LEVEL | GPIO_INT_ACTIVE_HIGH
			| PULL_UP;
		break;
	case CHANGE:
		gpio_mode = GPIO_DIR_IN | GPIO_INT
			| GPIO_INT_DOUBLE_EDGE | GPIO_INT_ACTIVE_LOW
			| GPIO_INT_ACTIVE_HIGH | PULL_UP;
		break;
	case FALLING:
		gpio_mode = GPIO_DIR_IN | GPIO_INT
			| GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW
			| PULL_UP;
		break;
	case RISING:
		gpio_mode = GPIO_DIR_IN | GPIO_INT
			| GPIO_INT_EDGE | GPIO_INT_ACTIVE_HIGH
			| PULL_UP;
		break;
	default:
		gpio_mode = GPIO_DIR_IN | GPIO_INT
			| GPIO_INT_DOUBLE_EDGE | GPIO_INT_ACTIVE_LOW
			| GPIO_INT_ACTIVE_HIGH | PULL_UP;
	}

	gpiob = device_get_binding(PORT);

	

	gpio_pin_configure(gpiob, zephyrDescription[pin].zephyrPin1, gpio_mode);

	gpio_init_callback(&gpio_cb, callback, BIT(zephyrDescription[pin].zephyrPin1));
	gpio_add_callback(gpiob, &gpio_cb);

	gpio_pin_enable_callback(gpiob, zephyrDescription[pin].zephyrPin1);

}

void detachInterrupt(uint32_t pin)
{
	struct device *gpiob;
	gpiob = device_get_binding(PORT);

	gpio_pin_disable_callback(gpiob, zephyrDescription[pin].zephyrPin1);
}

void interrupts(void)
{
	//enable interrupts
}

void noInterrupts(void)
{
	//disable interrupts
}

#ifndef variant_h
#define variant_h

#include "pins_arduino.h"
#include <pinmux.h>

#ifdef __cplusplus
extern "C" {
#endif

void variantInit();

//mux modes
#define I2C_MUX_MODE	PINMUX_FUNC_A
#define SPI_MUX_MODE	PINMUX_FUNC_B
#define I2S_MUX_MODE	PINMUX_FUNC_B
#define GPIO_MUX_MODE	PINMUX_FUNC_A
#define PWM_MUX_MODE	PINMUX_FUNC_B

#ifdef __cplusplus
}
#endif

#endif // variant_h

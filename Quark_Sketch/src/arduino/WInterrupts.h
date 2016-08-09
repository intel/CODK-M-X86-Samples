#ifndef _WIRING_INTERRUPTS_
#define _WIRING_INTERRUPTS_

#include "arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

void attachInterrupt(uint32_t pin, void (*callback)(void), uint32_t mode);

void detachInterrupt(uint32_t pin);

void interrupts(void);

void noInterrupts(void);

#ifdef __cplusplus
}
#endif

#endif

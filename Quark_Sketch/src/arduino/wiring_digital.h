#ifndef WIRING_DIGITAL_H
#define WIRING_DIGITAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void digitalInit();

void pinMode(uint8_t pin, uint8_t mode);

void digitalWrite(uint8_t pin, uint8_t level);

int digitalRead(uint8_t pin);

#ifdef __cplusplus
}
#endif


#endif //WIRING_DIGITAL_H



#ifndef Arduino_h
#define Arduino_h


#include "variant.h"
#include "wiring_digital.h"
#include "wiring_analog.h"
#include "WInterrupts.h"
#include "wiring.h"

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x01
#define INPUT_PULLUP 0x02

#define INVALID 255
#define SS_GPIO	0x00
#define SOC_GPIO 0x01

#ifdef __cplusplus
extern "C" {
#endif

void setup( void );
void loop( void );

typedef struct _ZephyrPinDescription
{
	uint8_t arduinoPin;
	uint8_t zephyrPin1;
	uint8_t zephyrPin2;
	uint8_t analogPinNumber;
	uint8_t pwmChannel;
	uint8_t pinMode;
	uint8_t fabric;
} ZephyrPinDescription;

extern ZephyrPinDescription zephyrDescription[];

#ifdef __cplusplus
}
#endif



#endif // Arduino_h

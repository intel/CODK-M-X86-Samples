#ifndef SERIAL_PRINT_H
#define SERIAL_PRINT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int serial_print(const char *buf);

int serial_println(const char *buf);

int serial_printInt(int val);

int serial_printFloat(float f, int digits);

int serial_printChar(char c);

int serial_write(const uint8_t uc_data);

uint16_t serial_available();

uint16_t serial_availableForWrite();

int serial_peek();

int serial_read();

void serial_flush();

int serial_device_isopen();

int serial_host_isopen();

#ifdef __cplusplus
}
#endif


#endif //SERIAL_PRINT_H


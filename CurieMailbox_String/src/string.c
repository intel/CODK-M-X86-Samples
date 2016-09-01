#include <zephyr.h>
#include <device.h>
#include <ipm.h>
#include <ipm/ipm_quark_se.h>
#include "soc.h"

#define SLEEP_TIME 100

/* Sending messages on channel 1 */
QUARK_SE_IPM_DEFINE(ipm_send, 0, QUARK_SE_IPM_OUTBOUND);

const char data[] = "Hello from x86";

void main (void)
{
    struct device *ipm = device_get_binding("ipm_send");

    while (1) {
        task_sleep(SLEEP_TIME);
        ipm_send(ipm, 1, 0, data, 16);
    }
}

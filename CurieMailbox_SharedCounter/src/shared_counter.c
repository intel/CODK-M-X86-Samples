#include <zephyr.h>
#include <device.h>
#include <ipm.h>
#include <ipm/ipm_quark_se.h>
#include "soc.h"

/* Sending messages on channel 1 */
QUARK_SE_IPM_DEFINE(ipm_send, 1, QUARK_SE_IPM_OUTBOUND);

/* Receiving messages on channel 0 */
QUARK_SE_IPM_DEFINE(ipm_receive, 0, QUARK_SE_IPM_INBOUND);

static struct device *ipm;
static volatile uint32_t val;
static volatile bool received;

void ipm_callback(void *context, uint32_t id, volatile void *data)
{
	uint32_t *udata = (uint32_t *)data;
    val = *udata + 1;
    received = true;
}

void main (void)
{
	struct device *rec_ipm;

    received = false;
    ipm = device_get_binding("ipm_send");
	rec_ipm = device_get_binding("ipm_receive");
	ipm_register_callback(rec_ipm, ipm_callback, NULL);
	ipm_set_enabled(rec_ipm, 1);

    while (1) {
        if (received) {
            received = false;
            ipm_send(ipm, 1, 0, (uint32_t *)&val, sizeof(uint32_t));
        }
    }
}

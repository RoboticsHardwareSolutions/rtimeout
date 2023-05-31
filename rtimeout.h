#ifndef __RTIMEOUT_H__
#define __RTIMEOUT_H__

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include <sys/time.h>
#include <time.h>
#include <signal.h>

typedef struct
{
    struct timeval start_time;
    uint32_t       timeout;
} rt;

int rt_set(rt* instance, uint32_t timeout_us);

/** timed out?
 * @param instance - timeout instance
 * @return -1 if error
 *          0 if timeout not elapsed
 *          1 already if timed out
 */
int rt_timed_out(rt* instance);

int rt_is_enabled(rt* instance);

#endif

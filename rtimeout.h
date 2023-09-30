#ifndef __RTIMEOUT_H__
#define __RTIMEOUT_H__

#include "rtimeout_def.h"

int rt_set(rt* instance, unsigned long timeout_us);

/** timed out?
 * @param instance - timeout instance
 * @return -1 if error
 *          0 if timeout not elapsed
 *          1 already if timed out
 */
int rt_timed_out(rt* instance);

int rt_is_enabled(rt* instance);

#endif

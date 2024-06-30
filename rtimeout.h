#ifndef __RTIMEOUT_H__
#define __RTIMEOUT_H__

#include "rtimeout_def.h"

/** @brief set timeout for an instance
 * @param instance - timeout the instance
 * @return -1 if error
 *          0 if ok
 */
int rt_set(rt* instance, unsigned long timeout_us);

/** timed out?
 * @param instance - timeout the instance
 * @return -1 if error
 *          0 if timeout not elapsed
 *          1 already if timed out
 */
int rt_timed_out(rt* instance);

/** @brief the instance is enable
 * @param instance - timeout the instance
 * @return -1 if error
 *          0 if timed out
 *          1 if the instance is in process
 */
int rt_is_enabled(rt* instance);

#endif

#include "rtimeout.h"
#include <time.h>

inline int rt_set(rt* instance, uint32_t timeout_us)
{
    if (instance == NULL || timeout_us == 0)
    {
        return -1;
    }

    if (gettimeofday(&instance->start_time, NULL) != 0)
    {
        return -1;
    }
    instance->timeout = timeout_us;
    return 0;
}

inline int rt_timed_out(rt* instance)
{
    if (instance == NULL)
        return -1;

    struct timeval current_time;
    if (gettimeofday(&current_time, NULL) != 0)
    {
        return -1;
    }
    uint32_t elapsed_time = (uint32_t) ((current_time.tv_sec - instance->start_time.tv_sec) * 1000000 +
                                        current_time.tv_usec - instance->start_time.tv_usec);

    bool result = instance->timeout > 0 && elapsed_time > instance->timeout ? 1 : 0;

    if (result)
    {
        instance->timeout = 0;
    }
    return result;
}

inline int rt_is_enabled(rt* instance)
{
    if (instance == NULL)
        return -1;

    return instance->timeout > 0 ? 1 : 0;
}

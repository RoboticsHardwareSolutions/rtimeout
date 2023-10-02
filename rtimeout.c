#include "rtimeout.h"

#if defined(STM32F072xB) || defined(STM32F091xC) || defined(STM32F103xB) || defined(STM32F407xx) || \
    defined(STM32F429xx) || defined(STM32F103xE) || defined(STM32F765xx) || defined(STM32G474xx)

inline int rt_set(rt* instance, unsigned long timeout_us)
{
    if (instance == NULL || timeout_us == 0)
    {
        return -1;
    }

    instance->start_time = osKernelSysTick();
    instance->timeout    = timeout_us / 1000;
    return 0;
}

inline int rt_timed_out(rt* instance)
{
    if (instance == NULL)
        return -1;

    unsigned long current_time = osKernelSysTick();
    unsigned long elapsed_time = current_time - instance->start_time;
    int           result       = instance->timeout > 0 && elapsed_time > instance->timeout ? 1 : 0;

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

#endif

#if defined(RTIMEOUT_FOR_WINDOWS) || defined(RTIMEOUT_FOR_UNIX) || defined(RTIMEOUT_FOR_APPLE)

int rt_set(rt* instance, unsigned long timeout_us)
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

#endif

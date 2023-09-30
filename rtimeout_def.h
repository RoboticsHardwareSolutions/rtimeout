#pragma once

#if defined(STM32G474xx) || defined(STM32F103xB) || defined(STM32F072xB) || defined(STM32F091xC) || \
    defined(STM32F407xx) || defined(STM32F429xx) || defined(STM32F765xx) || defined(STM32F103xE)

#    include "cmsis_os.h"

typedef struct
{
    unsigned long start_time;
    unsigned long timeout;
} rt;

#endif

#if defined(RSERIAL_FOR_APPLE) || defined(RSERIAL_FOR_UNIX) || defined(RSERIAL_FOR_WINDOWS)

#    include "stdio.h"
#    include "stdbool.h"
#    include "stdint.h"
#    include <sys/time.h>
#    include <time.h>
#    include <signal.h>

typedef struct
{
    struct timeval start_time;
    uint32_t       timeout;
} rt;

#endif

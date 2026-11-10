#pragma once

#if defined(RTIMEOUT_FOR_RHS)

#    include "stdint.h"

/* RHS core, kernel.h: the RTOS tick, it can be read in an interrupt and before the scheduler starts */
uint32_t rhs_get_tick(void);
uint32_t rhs_kernel_get_tick_frequency(void);

#    define get_tick() ((unsigned long) ((uint64_t) rhs_get_tick() * 1000U / rhs_kernel_get_tick_frequency()))

typedef struct
{
    unsigned long start_time;
    unsigned long timeout;
} rt;

#elif defined(STM32G474xx) || defined(STM32F103xB) || defined(STM32F072xB) || defined(STM32F091xC) || \
    defined(STM32F407xx) || defined(STM32F429xx) || defined(STM32F765xx) || defined(STM32F103xE) ||   \
    defined(STM32G0B1xx)

#    ifdef CMSIS_OS_H_
#        include "cmsis_os.h"
#        define get_tick() osKernelSysTick()
#    else
#        if defined(STM32F765xx)
#            include "stm32f7xx_hal.h"
#        elif defined(STM32G0B1xx)
#            include "stm32g0xx_hal.h"
#        elif defined(STM32G474xx)
#            include "stm32g4xx_hal.h"
#        elif defined(STM32F429xx) || defined(STM32F407xx)
#            include "stm32f4xx_hal.h"
#        elif defined(STM32F103xE)
#            include "stm32f1xx_hal.h"
#        elif defined(STM32F091xC) || defined(STM32F072xB)
#            include "stm32f0xx_hal.h"
#        endif
#        define get_tick() HAL_GetTick()
#    endif

typedef struct
{
    unsigned long start_time;
    unsigned long timeout;
} rt;

#endif

#if defined(RTIMEOUT_FOR_APPLE) || defined(RTIMEOUT_FOR_UNIX) || defined(RTIMEOUT_FOR_WINDOWS)

#    include "stdbool.h"
#    include "stdint.h"
#    include "stdio.h"
#    include <signal.h>
#    include <sys/time.h>
#    include <time.h>

typedef struct
{
    struct timeval start_time;
    uint32_t       timeout;
} rt;

#endif

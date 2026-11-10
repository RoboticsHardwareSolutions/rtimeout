# rtimeout

Compatibility with Linux, MacOS, Windows and STM32

On STM32 the tick is `HAL_GetTick()`. With `RTIMEOUT_FOR_RHS` defined it is the tick of the RHS core,
`rhs_get_tick()`: use it when FreeRTOS owns SysTick and nothing advances the HAL tick.

Example:
```c
rt timeout;

int main()
{
    rt_set(&timeout, 5000000); // set timeout 5 sec

    while(rt_timed_out(&timeout) != 1); // wait while timed out

    return 0;
}
```

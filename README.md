# rtimeout

Compatibility with Linux, MacOS, Windows and STM32

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

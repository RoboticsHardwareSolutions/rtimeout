#include "runit/src/runit.h"
#include "../rtimeout.h"
#include "unistd.h"

void test_timeout(void)
{
    rt timeout = {0};

    runit_true(rt_set(NULL, 100000) == -1);
    runit_true(rt_set(&timeout, 0) == -1);
    runit_true(rt_is_enabled(NULL) == -1);
    runit_true(rt_timed_out(NULL) == -1);

    runit_true(rt_is_enabled(&timeout) == 0);
    runit_true(rt_set(&timeout, 1000000) == 0);
    runit_true(rt_is_enabled(&timeout) == 1);
    runit_true(rt_timed_out(&timeout) == 0);
    runit_true(rt_timed_out(&timeout) == 0);
    usleep(1000100);
    runit_true(rt_timed_out(&timeout) == 1);
    runit_true(rt_is_enabled(&timeout) == 0);

    runit_true(rt_set(&timeout, 1000000) == 0);
    runit_true(rt_timed_out(&timeout) == 0);
    usleep(1000100);
    runit_true(rt_timed_out(&timeout) == 1);
}

int main()
{
    test_timeout();
    runit_report();
    return runit_at_least_one_fail;
}

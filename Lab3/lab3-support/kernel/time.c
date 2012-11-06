#include <arm/timer.h>

unsigned long time()
{
    return get_clock();
}


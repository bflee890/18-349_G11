#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>

unsigned long time()
{
    return get_oscr();
}


/* 
    The actual kernel code are here
*/

#include "kernel.h"

extern void kernelMain()
{
    MoeP::kernel::printf("kernel booted");
    while(true);
}


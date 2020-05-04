/*
    preforms all the hardware initialization before switching to user mode
    loader.s will call the bootKernel function to boot the system
    TODO:
    
*/

#include <MoeP/types.h>

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor *i = &start_ctors; i != &end_ctors; ++i)
    {
        (*i)();
    }
}

extern void kernelMain();
void shutdown();

extern "C" void bootKernel(void* multiboot_structure, uint32 magicNum)
{
    //place for some pre-kernel initialization
    //for now, just boot the kernel
    kernelMain();

    shutdown();
}

void shutdown()
{

}


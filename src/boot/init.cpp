/*
    preforms all the hardware initialization before switching to user mode
    loader.s will call the bootKernel function to boot the system
    TODO:
    put utility functions (printf) to somewhere else
*/

#include <com/types.h>
#include <kernel/printf.h>

#define VGA_TEXT_MEMORY 0xB8000;

static uint8 x = 0, y = 0;

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


extern "C" void bootKernel(void* multiboot_structure, uint32 magicNum)
{
    //clearScreen();
    MoeP::kernel::printf("Hello World!\n");
    MoeP::kernel::printf("This is a simple OS.\n");
    MoeP::kernel::printf("Number test %d%d.\n", -123, 456);
    while(true);
}


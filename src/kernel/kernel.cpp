/* 
    The actual kernel code are here
*/

#include "kernel.h"
#include <kernel/printf.h>
#include <kernel/gdt.h>
#include <kernel/interrupt.h>
#include <hardware/keyboard.h>
#include <hardware/driver.h>
#include <hardware/console.h>

using namespace MoeP;
using namespace MoeP::kernel;

static bool shutdown = false;

extern void kernelMain()
{
    printf("Welcome to MoeP!\n");
    printf("This is a simple OS.\n");
    //initialization
    //setup global descriptor table
    GlobalDescriptorTable gdt = GlobalDescriptorTable();
    //setup interrupts and interrupt descriptor table
    InterruptManager interrupt = InterruptManager(&gdt);
    hardware::DriverManager drv = hardware::DriverManager();
    //initialize hardware
    hardware::KeyboardDriver keyboard(&interrupt);
    drv.AddDriver(&keyboard);

    hardware::ConsoleDriver console;
    console.Activate();

    interrupt.Activate();
    
    while(shutdown)
    {

    }
}
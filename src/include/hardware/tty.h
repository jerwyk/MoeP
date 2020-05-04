#pragma once
/*
    represents a terminal driver
*/

#include <MoeP/types.h>
#include <hardware/driver.h>
#include <hardware/console.h>
#include <hardware/keyboard.h>
#include <kernel/interrupt.h>

namespace MoeP
{
    namespace hardware
    {
        class TtyDriver : public Driver
        {
        private:
            //defines the console(output) and keyboard(input) of the terminal
            ConsoleDriver *console;
            KeyboardDriver *keyboard;

        public:
            TtyDriver(kernel::InterruptManager *manager);
            ~TtyDriver();


        };
    }
}
#pragma once

#include <MoeP/types.h>
#include <hardware/driver.h>

#define VGA_TEXT_MEMORY 0xB8000

namespace MoeP
{
    namespace hardware
    {
        class ConsoleDriver : public Driver
        {
        private:

            static ConsoleDriver *activeScreenDriver;

            //the current posistion
            uint32 x;
            uint32 y;
            int mode;

        public:
            //kernel print
            static void kprint(const char *str);

            ConsoleDriver();
            ~ConsoleDriver();
            virtual void Activate();
            virtual void Deactivate();
            void PutChar(const char ch);
            void ClearScreen();
            void Print(const char *str);
        };
    }
}
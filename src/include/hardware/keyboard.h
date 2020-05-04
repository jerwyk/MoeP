#pragma once

#include <MoeP/types.h>
#include <kernel/interrupt.h>
#include <hardware/driver.h>
#include <kernel/ports.h>

#define SCAN_RELEASE 0x80

namespace MoeP
{
    namespace hardware
    {
        class KeyboardDriver : public kernel::InterruptHandler, public hardware::Driver
        {
        private:
            Port<uint8> dataPort;
            Port<uint8> commandPort;
            //state of the function keys
            bool shift; //either shift key
            bool lShitf;
            bool rShift;
            bool ctrl;
            bool lCtrl;
            bool rCtrl;
            bool alt;
            bool lAlt;
            bool rAlt;
            bool caps;
            bool numLock;
            bool scrollLock;
            

        public:
            KeyboardDriver(kernel::InterruptManager *manager);
            ~KeyboardDriver();
            virtual uint32 HandleInterrupt(uint32 esp);
            virtual void Activate();
            virtual void Deactivate();
        };
    }
}
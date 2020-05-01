#pragma once

#include <MoeP/types.h>
#include <kernel/ports.h>
#include <kernel/gdt.h>

namespace MoeP
{
    namespace kernel
    {
        class InterruptManager;

        //Base class for handling interrups
        class InterruptHandler
        {
        protected:
            uint8 interruptNumber;
            //pointer to the interrupt manager
            InterruptManager *interruptManager;

            InterruptHandler(uint8 number, InterruptManager *manager);
            ~InterruptHandler();
        public:
            virtual uint32 HandleInterrupt(uint32 esp);

        };

        class InterruptManager
        {
        friend class InterruptHandler;
        protected:
            
            static InterruptManager *activeInterruptManager;
            //stores a list of interrupt handlers
            InterruptHandler *handlers[256];

            struct GateDescriptor
            {
                uint16 handlerAddressLow;
                uint16 gdtCodeSegmentSelector;
                uint8 reserved;
                uint8 access;
                uint16 handlerAdressHigh;
            }__attribute__((packed));
            
            static GateDescriptor _interruptDescriptorTable[256];

            struct IDTPointer
            {
                uint16 size;
                uint32 base;
            }__attribute__((packed));

            static void SetInterruptDescriptorTableEntry(uint8 interruptNum, uint16 codeSegmentSelectorOffset, void (*handler)(), uint8 DescriptorPrivilegeLevel, uint8 DescriptorType);

            PortSlow<uint8> picMasterCommand;
            PortSlow<uint8> picMasterData;
            PortSlow<uint8> picSlaveCommand;
            PortSlow<uint8> picSlaveData;

        public:
            InterruptManager(GlobalDescriptorTable *gdt);
            ~InterruptManager();

            void Activate();
            void Deactivate();

            static uint32 HandleInterrupt(uint8 interruptNum, uint32 esp);
            uint32 DoHandleInterrupt(uint8 interruptNum, uint32 esp);

            static void IgnoreInterruptRequest();
            static void HandleInterruptRequest0x00(); //timer
            static void HandleInterruptRequest0x01(); //keyboard
            static void HandleInterruptRequest0x0C(); //mouse

        };
    }
}
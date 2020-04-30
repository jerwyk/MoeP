#include <kernel/interrupt.h>

using namespace MoeP::kernel;

//interrupt handler
InterruptHandler::InterruptHandler(uint8 number, InterruptManager *manager)
{
    this->interruptNumber = number;
    this->interruptManager = manager;
    interruptManager->handlers[number] = this;
}

InterruptHandler::~InterruptHandler()
{
    if(interruptManager->handlers[interruptNumber] == this)
    {
        interruptManager->handlers[interruptNumber] = 0;
    }
}

uint32 InterruptHandler::HandleInterrupt(uint32 esp)
{

}

//interrupt manager
InterruptManager::GateDescriptor InterruptManager::_interruptDescriptorTable[256];

InterruptManager* InterruptManager::activeInterruptManager = 0;

uint32 InterruptManager::HandleInterrupt(uint8 interruptNum, uint32 esp)
{
    if(activeInterruptManager != 0)
    {
        //leave the static function
        activeInterruptManager->DoHandleInterrupt(interruptNum, esp);
    }
    return esp;
}

//actual functions to handle all the interrupts
uint32 InterruptManager::DoHandleInterrupt(uint8 interruptNum, uint32 esp)
{

    if(handlers[interruptNum] != 0)
    {
        esp = handlers[interruptNum]->HandleInterrupt(esp);
    }
    //only output if interrupt is not timer interrupts
    else if(interruptNum != 0x20)
    {
        char_t *errMsg = "UNHANDLED INTERRUPT 0x00\n";
        const char_t *hex = "0123456789ABCSEF";
        errMsg[22] = hex[(interruptNum >> 4) & 0x0F];
        errMsg[23] = hex[interruptNum & 0x0F];
    }

    //we only respond to hardware interrupts    
    //which are from 0x20 to 0x30
    if(0x20 <= interruptNum && interruptNum < 0x30)
    {
        picMasterCommand.Write(0x20);
        if(0x28 <= interruptNum)
        {
            picSlaveCommand.Write(0x20);
        }
    }
    
    return esp;
}

void InterruptManager::SetInterruptDescriptorTableEntry(uint8 interruptNum, uint16 codeSegmentSelectorOffset, void (*handler)(), uint8 DescriptorPrivilegeLevel, uint8 DescriptorType)
{
    const uint8 IDT_DESC_PRESENT = 0x80;

    _interruptDescriptorTable[interruptNum].handlerAddressLow = ((uint32)handler) & 0xFFFF;
    _interruptDescriptorTable[interruptNum].handlerAdressHigh = (((uint32)handler) >> 16) & 0xFFFF;
    _interruptDescriptorTable[interruptNum].gdtCodeSegmentSelector = codeSegmentSelectorOffset;
    _interruptDescriptorTable[interruptNum].reserved = 0;
    _interruptDescriptorTable[interruptNum].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilegeLevel & 3) << 5);
}

InterruptManager::InterruptManager(GlobalDescriptorTable *gdt)
: picMasterCommand(0x20), picMasterData(0x21), picSlaveCommand(0xA0), picSlaveData(0xA1)
{
    uint16 CodeSegment = gdt->CodeSegmentSelector();
    const uint8 IDT_INTERRUPT_GATE = 0xE;

    for(int i = 0; i < 256; ++i)
    {
        SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
        handlers[i] = 0;
    }

    SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x2C, CodeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);

    picMasterCommand.Write(0x11);
    picSlaveCommand.Write(0x11);

    picMasterData.Write(0x20);
    picSlaveData.Write(0x28);

    picMasterData.Write(0x04);
    picSlaveData.Write(0x02);

    picMasterData.Write(0x01);
    picSlaveData.Write(0x01);

    picMasterData.Write(0x00);
    picSlaveData.Write(0x00);

    //setup a pointer to the idt array
    IDTPointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32)_interruptDescriptorTable;
    //load it into the cpu
    asm volatile("lidt %0" : : "m" (idt));

}

void InterruptManager::Activate()
{
    //make sure there is only one interrupt manager
    if(activeInterruptManager != 0)
    {
        activeInterruptManager->Deactivate();
    }
    activeInterruptManager = this;
    asm("sti");
}

void InterruptManager::Deactivate()
{
    //if it is other stuff then its already deactivated
    if(activeInterruptManager == this)
    {
        activeInterruptManager = 0;
        //disable interrupts
        asm("cli");
    }
}

InterruptManager::~InterruptManager()
{}
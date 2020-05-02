#include <hardware/keyboard.h>
#include <kernel/printf.h>

#include "scancode.h"

using namespace MoeP;
using namespace MoeP::hardware;


KeyboardDriver::KeyboardDriver(kernel::InterruptManager *manager) : 
Driver(),
InterruptHandler(0x21, manager), 
dataPort(0x60), 
commandPort(0x64)
{

}

KeyboardDriver::~KeyboardDriver()
{

}

void KeyboardDriver::Activate()
{
    //wait until no key is being pressed
    while(commandPort.Read() & 0x01)
    {
        dataPort.Read();
    }

    commandPort.Write(0xAE);    //this tells the pic to start sending keyboard interrupts
    commandPort.Write(0x20);    //this gives the current state
    uint8 state = (dataPort.Read() | 1) & ~0x10; //read the state, set the right most bit to one, and clear the 5th bit
    commandPort.Write(0x60);    //command to set state
    dataPort.Write(state);      //set the state

    dataPort.Write(0xF4);       //activates the keyboard
}

void KeyboardDriver::Deactivate()
{

}

uint32 KeyboardDriver::HandleInterrupt(uint32 esp)
{
    //read the key from the pic
    uint8 key = dataPort.Read();
    const uint8 *scancodeLUT;
    //scancode extension
    if(key == SCAN_EXTEND1)
    {
        scancodeLUT = scancodeSet1EscapeLUT;
        key = dataPort.Read();
    }
    else
    {
        scancodeLUT = scancodeSet1LUT;
    }

    //key release
    int release = key & SCAN_RELEASE ? SCAN_RELEASE : 0x00;
    uint32 keycode = scancodeLUT[key & ~SCAN_RELEASE];
    //fornow:
    kernel::printf("%d\n", keycode | release);

}
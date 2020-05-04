#include <hardware/console.h>

using namespace MoeP::hardware;

ConsoleDriver* ConsoleDriver::activeScreenDriver = 0;

ConsoleDriver::ConsoleDriver() : Driver()
{

}

ConsoleDriver::~ConsoleDriver()
{}

void ConsoleDriver::Activate()
{
    activeScreenDriver = this;
}

void ConsoleDriver::Deactivate()
{
    activeScreenDriver = 0;
}

void ConsoleDriver::kprint(const char *str)
{
    if(activeScreenDriver != 0)
        activeScreenDriver->Print(str);
}

void ConsoleDriver::Print(const char *str)
{
    for(int i = 0; str[i] != '\0'; ++i)
    {
        PutChar(str[i]);
    }
}

void ConsoleDriver::PutChar(const char ch)
{
    //unsigned short so that one entry is 2 bytes
    //in ram starting from 0xb8000, for each 2 bytes
    //the high byte contains the color information
    //the low byte is the letter to print to the screen
    uint16 *videoMemory = (uint16*)VGA_TEXT_MEMORY;
    //detect escape characters
    switch (ch)
    {
        case '\n':
            ++y;
            x = 0;
            break;    
        default:
            //only overwrites the low byte
            videoMemory[80*y+x] = (videoMemory[80*y+x] & 0xFF00) | ch;
            ++x;
            break;
    }

    if(x >= 80)
    {
        ++y;
        x = 0;
    }
    if(y >= 25)
    {
        ClearScreen();
        x = y = 0;
    }
}

void ConsoleDriver::ClearScreen()
{
    uint16 *videoMemory = (uint16*)VGA_TEXT_MEMORY;
    for (int y = 0; y < 25; y++)
    {
        for (int x = 0; x < 80; x++)
        {
            videoMemory[80*y+x] = (videoMemory[80*y+x] & 0xFF00) | ' ';
        }  
    }  
}
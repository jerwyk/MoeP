#include <com/types.h>

static uint8 x = 0, y = 0;

static int printf(const char *fmt, ...);
void clearScreen();
void putChar(const char ch);

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
    clearScreen();
    printf("Hello World!\n");
    printf("This is a simple OS.\n");
    while(true);
}

static int printf(const char *fmt, ...)
{
    for(int i = 0; fmt[i] != '\0'; ++i)
    {
        putChar(fmt[i]);
    }
    return 0;
}

void putChar(const char ch)
{
    //unsigned short so that one entry is 2 bytes
    //in ram starting from 0xb8000, for each 2 bytes
    //the high byte contains the color information
    //the low byte is the letter to print to the screen
    uint16 *videoMemory = (uint16*)0xb8000;
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
        clearScreen();
        x = y = 0;
    }
}

void clearScreen()
{
    uint16 *videoMemory = (uint16*)0xb8000;
    for (int y = 0; y < 25; y++)
    {
        for (int x = 0; x < 80; x++)
        {
            videoMemory[80*y+x] = (videoMemory[80*y+x] & 0xFF00) | ' ';
        }
        
    }  
}   


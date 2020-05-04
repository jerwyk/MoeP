#include <kernel/printf.h>
#include <hardware/console.h>

//flages for formatting
#define UPPER_CASE      1
#define ALT_FORM        2
#define LEFT_JUSTIFY    4
#define BLANK_SPACE     8
#define LEFT_PAD        16
#define FORCE_SIGN      32
    
static char* printBuf;

//this is supposed to be a system call...
//but thats for later
void putChar(const char ch);
void clearScreen();
char* itos(int num);

char* itos(char *str, int num, int base, int flags)
{
    //hex digits
    const char *digits = flags & UPPER_CASE ? "0123456789ABCDEF" : "0123456789abcdef";

    //handle the flags
    if(flags & ALT_FORM)
    {
        switch (base)
        {
        case 16:
            *str++ = '0';
            *str++ = 'x';
            break;
        
        default:
            break;
        }
    }

    //negative numbers
    if(num < 0)
    {
        *str++ = '-';
        num *= -1;
    }

    int length = 0;
    int tmp = num;
    do
    {
        tmp /= base;
        ++length;
    } while (tmp > 0);
    //stores the length
    tmp = length;
    while(tmp --> 0)
    {
        *(str + tmp) = digits[num % base];
        num /= base;
    }
    str += length;
    return str;
}

int MoeP::kernel::printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

//does the actual formatting
//we dont have streams yet
int MoeP::kernel::vsprintf(char *s, const char *fmt, va_list arg)
{
    int i = 0;
    char *str;

    int flags = 0;

    for(str = s; *fmt; ++fmt)
    {
        //format character
        if(*fmt == '%')
        {
            //parse flags
            bool endFlags = false;
            while(!endFlags)
            {
                ++fmt;
                switch (*fmt)
                {
                case '#':
                    flags |= ALT_FORM; break;
                case '-':
                    flags |= LEFT_JUSTIFY; break;  
                case '+':
                    flags |= FORCE_SIGN; break;              
                case '0':
                    flags |= LEFT_PAD; break; 
                case ' ':
                    flags |= BLANK_SPACE; break; 
                default:
                    endFlags = true; break;
                }
            }

            //parse specifier
            switch (*fmt)
            {
            case 'i':
            case 'd':
                str = itos(str, va_arg(arg, int), 10, flags);
                break; 
            case 'X':
                flags |= UPPER_CASE;
            case 'x':
                str = itos(str, va_arg(arg, int), 16, flags);
                break;
            case 'o':
                str = itos(str, va_arg(arg, int), 8, flags);
                break;
            default:
                break;
            }
        }
        else
        {
            *str++ = *fmt;
        }
        
    }
static 

}

//wraps around vsprintf
int MoeP::kernel::vprintf(const char * fmt, va_list arg)
{
    char s[1024];
    int i = vsprintf(s, fmt, arg);
    //we dont have streams yet..
    hardware::ConsoleDriver::kprint(s);
    return i;
}
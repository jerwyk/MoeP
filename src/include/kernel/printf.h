#pragma once

#include <com/util.h>
#include <stdarg.h>

/*
    since we have no stdlib, we have to impliment our own prinft
    for now, it directly prints to video memory
    heavly influnced by the linux kernel
*/

namespace MoeP
{
    namespace kernel
    {
        int printf(const char *fmt, ...);
        int sprintf(char * str, const char * fmt, ... );
        int vsprintf(char * s, const char * fmt, va_list arg);
        int vprintf(const char * fmt, va_list arg);
    }
}
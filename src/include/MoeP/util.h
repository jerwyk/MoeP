#pragma once

#ifdef DEBUG
//magic break for the bochs emulator, used for debugging
#define MAGIC_BREAK asm volatile("xchgw %bx, %bx")
#endif // DEBUG

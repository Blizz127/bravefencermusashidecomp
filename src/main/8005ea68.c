#include "psx_types.h"

/* Exact bounded controller export [8005EA68,8005EA88), 8 retail words. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005EA68\n"
    ".type func_8005EA68, @function\n"
    "func_8005EA68:\n"
    ".word 0x2402004c\n"
    ".word 0xa0820036\n"
    ".word 0x24820024\n"
    ".word 0xac82002c\n"
    ".word 0x24020001\n"
    ".word 0xa0850024\n"
    ".word 0x03e00008\n"
    ".word 0xa0820035\n"
    ".size func_8005EA68, .-func_8005EA68\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x2402004c)
MUSASHI_NATIVE_MIPS_WORD(0xa0820036)
MUSASHI_NATIVE_MIPS_WORD(0x24820024)
MUSASHI_NATIVE_MIPS_WORD(0xac82002c)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xa0850024)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0xa0820035)
#endif

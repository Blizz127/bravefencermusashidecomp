#include "psx_types.h"

/* Exact bounded controller export [8005EA54,8005EA68), 5 retail words. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005EA54\n"
    ".type func_8005EA54, @function\n"
    "func_8005EA54:\n"
    ".word 0x24020045\n"
    ".word 0xa0820036\n"
    ".word 0xac80002c\n"
    ".word 0x03e00008\n"
    ".word 0xa0800035\n"
    ".size func_8005EA54, .-func_8005EA54\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020045)
MUSASHI_NATIVE_MIPS_WORD(0xa0820036)
MUSASHI_NATIVE_MIPS_WORD(0xac80002c)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0xa0800035)
#endif

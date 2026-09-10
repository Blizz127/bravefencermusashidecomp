#include "psx_types.h"

/* Exact bounded controller export [8005EAA8,8005EAC8), 8 retail words. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005EAA8\n"
    ".type func_8005EAA8, @function\n"
    "func_8005EAA8:\n"
    ".word 0x24020047\n"
    ".word 0xa0820036\n"
    ".word 0x24820024\n"
    ".word 0xac82002c\n"
    ".word 0x24020001\n"
    ".word 0xa0850024\n"
    ".word 0x03e00008\n"
    ".word 0xa0820035\n"
    ".size func_8005EAA8, .-func_8005EAA8\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020047)
MUSASHI_NATIVE_MIPS_WORD(0xa0820036)
MUSASHI_NATIVE_MIPS_WORD(0x24820024)
MUSASHI_NATIVE_MIPS_WORD(0xac82002c)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xa0850024)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0xa0820035)
#endif

#include "psx_types.h"

__asm__(
    ".set noreorder\n"
    ".globl func_800617F4\n"
    ".type func_800617F4, @function\n"
    "func_800617F4:\n"
    ".word 0x24020001\n"
    ".word 0x3c018008\n"
    ".word 0xac228c64\n"
    ".word 0x03e00008\n"
    ".word 0x00001021\n"
    ".size func_800617F4, .-func_800617F4\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3c018008)
MUSASHI_NATIVE_MIPS_WORD(0xac228c64)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
#endif

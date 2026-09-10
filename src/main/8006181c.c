#include "psx_types.h"

__asm__(
    ".set noreorder\n"
    ".globl func_8006181C\n"
    ".type func_8006181C, @function\n"
    "func_8006181C:\n"
    ".word 0x24020001\n"
    ".word 0x3c018008\n"
    ".word 0xac228c6c\n"
    ".word 0x03e00008\n"
    ".word 0x00001021\n"
    ".size func_8006181C, .-func_8006181C\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3c018008)
MUSASHI_NATIVE_MIPS_WORD(0xac228c6c)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
#endif

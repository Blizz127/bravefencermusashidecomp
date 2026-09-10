#include "psx_types.h"

__asm__(
    ".set noreorder\n"
    ".globl func_80061830\n"
    ".type func_80061830, @function\n"
    "func_80061830:\n"
    ".word 0x24020001\n"
    ".word 0x3c018008\n"
    ".word 0xac228c70\n"
    ".word 0x03e00008\n"
    ".word 0x00001021\n"
    ".size func_80061830, .-func_80061830\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3c018008)
MUSASHI_NATIVE_MIPS_WORD(0xac228c70)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
#endif

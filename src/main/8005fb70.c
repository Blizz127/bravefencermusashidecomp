#include "psx_types.h"

/* Exact bounded controller export [8005FB70,8005FB9C), 11 retail words. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005FB70\n"
    ".type func_8005FB70, @function\n"
    "func_8005FB70:\n"
    ".word 0x948200e6\n"
    ".word 0x00000000\n"
    ".word 0x10400005\n"
    ".word 0x240200ff\n"
    ".word 0x90830046\n"
    ".word 0x00000000\n"
    ".word 0x10620002\n"
    ".word 0x00001021\n"
    ".word 0x24020001\n"
    ".word 0x03e00008\n"
    ".word 0x00000000\n"
    ".size func_8005FB70, .-func_8005FB70\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x948200e6)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x240200ff)
MUSASHI_NATIVE_MIPS_WORD(0x90830046)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10620002)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

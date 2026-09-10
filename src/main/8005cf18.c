#include "psx_types.h"

/* Retail startup service wrapper; native execution supplies the exception owner. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005CF18\n"
    ".type func_8005CF18, @function\n"
    "func_8005CF18:\n"
    "addiu $a0,$zero,2\n"
    "syscall\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8005CF18, .-func_8005CF18\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24040002)
MUSASHI_NATIVE_MIPS_WORD(0x0000000c)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

#include "psx_types.h"

/* Exact input serial wait helper [8005E13C,8005E164), 10 retail words. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005E13C\n"
    ".type func_8005E13C, @function\n"
    "func_8005E13C:\n"
    ".word 0x3c038007\n"
    ".word 0x8c6329c0\n"
    ".word 0x00000000\n"
    ".word 0x94620004\n"
    ".word 0x00000000\n"
    ".word 0x30420002\n"
    ".word 0x1040fffc\n"
    ".word 0x00000000\n"
    ".word 0x03e00008\n"
    ".word 0x00000000\n"
    ".size func_8005E13C, .-func_8005E13C\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c038007)
MUSASHI_NATIVE_MIPS_WORD(0x8c6329c0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x94620004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420002)
MUSASHI_NATIVE_MIPS_WORD(0x1040fffc)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif


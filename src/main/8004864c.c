/* Main-exec range [8004864C,8004867C) from the SLUS executable.
 * SHA256(span)=81613e199dfb7f10428c16787996391bf684672628d5f4251378aeec35b16441.
 * Word export for the native seam; the C body below keeps its
 * own oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C880000)
MUSASHI_NATIVE_MIPS_WORD(0x8C890004)
MUSASHI_NATIVE_MIPS_WORD(0x48880000)
MUSASHI_NATIVE_MIPS_WORD(0x48890800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A486012)
MUSASHI_NATIVE_MIPS_WORD(0xE8A90000)
MUSASHI_NATIVE_MIPS_WORD(0xE8AA0004)
MUSASHI_NATIVE_MIPS_WORD(0xE8AB0008)
MUSASHI_NATIVE_MIPS_WORD(0x00C01021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004864C\n"
    ".type func_8004864C, @function\n"
    "func_8004864C:\n"
    "lw $t0, 0x0($a0)\n"
    "lw $t1, 0x4($a0)\n"
    "mtc2 $t0, $0\n"
    "mtc2 $t1, $1\n"
    "nop\n"
    ".word 0x4A486012\n"
    "swc2 $9, 0x0($a1)\n"
    "swc2 $10, 0x4($a1)\n"
    "swc2 $11, 0x8($a1)\n"
    "addu $v0, $a2, $zero\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004864C, .-func_8004864C\n"
    ".set reorder\n"
);
#endif

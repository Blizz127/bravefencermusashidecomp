/* Main-exec range [800494FC,8004952C) from the SLUS executable.
 * SHA256(span)=e66be43eb3adaeb0d259561707274ef24c67a8589f293ee703a80247bd4fe056.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x84820000)
MUSASHI_NATIVE_MIPS_WORD(0x84830002)
MUSASHI_NATIVE_MIPS_WORD(0x48824800)
MUSASHI_NATIVE_MIPS_WORD(0x48835000)
MUSASHI_NATIVE_MIPS_WORD(0xC88B0004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4AA80428)
MUSASHI_NATIVE_MIPS_WORD(0xE8A90000)
MUSASHI_NATIVE_MIPS_WORD(0xE8AA0004)
MUSASHI_NATIVE_MIPS_WORD(0xE8AB0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00A01021)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800494FC\n"
    ".type func_800494FC, @function\n"
    "func_800494FC:\n"
    "lh $v0, 0x0($a0)\n"
    "lh $v1, 0x2($a0)\n"
    "mtc2 $v0, $9\n"
    "mtc2 $v1, $10\n"
    "lwc2 $11, 0x4($a0)\n"
    "nop\n"
    ".word 0x4AA80428\n"
    "swc2 $9, 0x0($a1)\n"
    "swc2 $10, 0x4($a1)\n"
    "swc2 $11, 0x8($a1)\n"
    "jr $ra\n"
    "addu $v0, $a1, $zero\n"
    ".size func_800494FC, .-func_800494FC\n"
    ".set reorder\n"
);
#endif

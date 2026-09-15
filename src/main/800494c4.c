/* Main-exec range [800494C4,800494FC) from the SLUS executable.
 * SHA256(span)=67bf54114c3507173f8649712e85d03d189c1a0ec13bbdd1ebcdc588ed474564.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x84820000)
MUSASHI_NATIVE_MIPS_WORD(0x84830002)
MUSASHI_NATIVE_MIPS_WORD(0x48824800)
MUSASHI_NATIVE_MIPS_WORD(0x48835000)
MUSASHI_NATIVE_MIPS_WORD(0xC88B0004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4AA00428)
MUSASHI_NATIVE_MIPS_WORD(0x48024800)
MUSASHI_NATIVE_MIPS_WORD(0x48035000)
MUSASHI_NATIVE_MIPS_WORD(0xE8AB0004)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A30002)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00A01021)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800494C4\n"
    ".type func_800494C4, @function\n"
    "func_800494C4:\n"
    "lh $v0, 0x0($a0)\n"
    "lh $v1, 0x2($a0)\n"
    "mtc2 $v0, $9\n"
    "mtc2 $v1, $10\n"
    "lwc2 $11, 0x4($a0)\n"
    "nop\n"
    ".word 0x4AA00428\n"
    "mfc2 $v0, $9\n"
    "mfc2 $v1, $10\n"
    "swc2 $11, 0x4($a1)\n"
    "sh $v0, 0x0($a1)\n"
    "sh $v1, 0x2($a1)\n"
    "jr $ra\n"
    "addu $v0, $a1, $zero\n"
    ".size func_800494C4, .-func_800494C4\n"
    ".set reorder\n"
);
#endif

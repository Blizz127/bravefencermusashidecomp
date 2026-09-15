/* Main-exec range [800539F8,80053A18) from the SLUS executable.
 * SHA256(span)=3eccebd144d7b6f0d0646a1f467529f2fc7e48c9710d690f881bd866ac476944.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8800000)
MUSASHI_NATIVE_MIPS_WORD(0xC8810004)
MUSASHI_NATIVE_MIPS_WORD(0xC8A20000)
MUSASHI_NATIVE_MIPS_WORD(0xC8A30004)
MUSASHI_NATIVE_MIPS_WORD(0xC8C40000)
MUSASHI_NATIVE_MIPS_WORD(0xC8C50004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800539F8\n"
    ".type func_800539F8, @function\n"
    "func_800539F8:\n"
    "lwc2 $0, 0x0($a0)\n"
    "lwc2 $1, 0x4($a0)\n"
    "lwc2 $2, 0x0($a1)\n"
    "lwc2 $3, 0x4($a1)\n"
    "lwc2 $4, 0x0($a2)\n"
    "lwc2 $5, 0x4($a2)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800539F8, .-func_800539F8\n"
    ".set reorder\n"
);
#endif

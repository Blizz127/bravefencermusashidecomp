/* Main-exec range [80053A60,80053A78) from the SLUS executable.
 * SHA256(span)=72d848610c07f57d296c6b6b120efcfab9a91cee5d935a03dd4f2f11bde50ef6.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48848000)
MUSASHI_NATIVE_MIPS_WORD(0x48858800)
MUSASHI_NATIVE_MIPS_WORD(0x48869000)
MUSASHI_NATIVE_MIPS_WORD(0x48879800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A60\n"
    ".type func_80053A60, @function\n"
    "func_80053A60:\n"
    "mtc2 $a0, $16\n"
    "mtc2 $a1, $17\n"
    "mtc2 $a2, $18\n"
    "mtc2 $a3, $19\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A60, .-func_80053A60\n"
    ".set reorder\n"
);
#endif

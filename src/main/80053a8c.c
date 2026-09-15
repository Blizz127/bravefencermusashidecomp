/* Main-exec range [80053A8C,80053AA0) from the SLUS executable.
 * SHA256(span)=ebf2ab5b55d34164ce9d996740d82449e99f98e4a65da7dcd9ad6e2f3cae7f17.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48C40000)
MUSASHI_NATIVE_MIPS_WORD(0x48C51000)
MUSASHI_NATIVE_MIPS_WORD(0x48C62000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A8C\n"
    ".type func_80053A8C, @function\n"
    "func_80053A8C:\n"
    "ctc2 $a0, $0\n"
    "ctc2 $a1, $2\n"
    "ctc2 $a2, $4\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A8C, .-func_80053A8C\n"
    ".set reorder\n"
);
#endif

/* Main-exec range [80053AC0,80053ACC) from the SLUS executable.
 * SHA256(span)=137430d515cfca2b9014536398a80cdb7341660e9b7ae4b91b8ffbe4fe866406.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48C4D800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053AC0\n"
    ".type func_80053AC0, @function\n"
    "func_80053AC0:\n"
    "ctc2 $a0, $27\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053AC0, .-func_80053AC0\n"
    ".set reorder\n"
);
#endif

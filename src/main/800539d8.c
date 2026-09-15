/* Main-exec range [800539D8,800539E8) from the SLUS executable.
 * SHA256(span)=31d133f533d6ea6694167ba27242e6f92ba829910c13a98083b1fb8ea360f562.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8820000)
MUSASHI_NATIVE_MIPS_WORD(0xC8830004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800539D8\n"
    ".type func_800539D8, @function\n"
    "func_800539D8:\n"
    "lwc2 $2, 0x0($a0)\n"
    "lwc2 $3, 0x4($a0)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800539D8, .-func_800539D8\n"
    ".set reorder\n"
);
#endif

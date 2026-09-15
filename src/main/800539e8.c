/* Main-exec range [800539E8,800539F8) from the SLUS executable.
 * SHA256(span)=1f5f773f52612acebf941e8e82f5296a637277bc37c7c344a4083d8090a338f9.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8840000)
MUSASHI_NATIVE_MIPS_WORD(0xC8850004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800539E8\n"
    ".type func_800539E8, @function\n"
    "func_800539E8:\n"
    "lwc2 $4, 0x0($a0)\n"
    "lwc2 $5, 0x4($a0)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800539E8, .-func_800539E8\n"
    ".set reorder\n"
);
#endif

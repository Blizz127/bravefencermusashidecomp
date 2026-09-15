/* Main-exec range [80053ACC,80053AD8) from the SLUS executable.
 * SHA256(span)=82fe222ec657dc8d11063c998d2a78c33a8c451f20b4c3e8f96d693f9a091070.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48C4E000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053ACC\n"
    ".type func_80053ACC, @function\n"
    "func_80053ACC:\n"
    "ctc2 $a0, $28\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053ACC, .-func_80053ACC\n"
    ".set reorder\n"
);
#endif

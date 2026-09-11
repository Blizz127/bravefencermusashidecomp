/* Main-exec range [800491EC,800491F8) from the SLUS executable.
 * SHA256(span)=4ecf2f5bbdb450de400e5eeafac260aaf27c3f5d36b3f67ef8ceb47855a2e800.
 * Word export for the native seam; the C body below keeps its
 * own oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x4842D000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800491EC\n"
    ".type func_800491EC, @function\n"
    "func_800491EC:\n"
    "cfc2 $v0, $26\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800491EC, .-func_800491EC\n"
    ".set reorder\n"
);
#endif

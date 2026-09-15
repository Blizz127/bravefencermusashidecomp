/* Main-exec range [8004936C,80049390) from the SLUS executable.
 * SHA256(span)=ca098524f15b22f4ea8ac38b7d348e2cdce3c58babac70b15baa82d7af5f4115.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48848000)
MUSASHI_NATIVE_MIPS_WORD(0x48858800)
MUSASHI_NATIVE_MIPS_WORD(0x48869000)
MUSASHI_NATIVE_MIPS_WORD(0x48879800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4B68002E)
MUSASHI_NATIVE_MIPS_WORD(0x48023800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004936C\n"
    ".type func_8004936C, @function\n"
    "func_8004936C:\n"
    "mtc2 $a0, $16\n"
    "mtc2 $a1, $17\n"
    "mtc2 $a2, $18\n"
    "mtc2 $a3, $19\n"
    "nop\n"
    ".word 0x4B68002E\n"
    "mfc2 $v0, $7\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004936C, .-func_8004936C\n"
    ".set reorder\n"
);
#endif

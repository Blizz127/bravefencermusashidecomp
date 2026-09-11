/* Main-exec range [80049324,8004934C) from the SLUS executable.
 * SHA256(span)=99cb1c8d0c79529e8c6f1a56f640ebd7400c2eb0f57312cdc2e252c1e34f201b.
 * Word export for the native seam; the C body below keeps its
 * own oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8890000)
MUSASHI_NATIVE_MIPS_WORD(0xC88A0004)
MUSASHI_NATIVE_MIPS_WORD(0xC88B0008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4AA00428)
MUSASHI_NATIVE_MIPS_WORD(0xE8B90000)
MUSASHI_NATIVE_MIPS_WORD(0xE8BA0004)
MUSASHI_NATIVE_MIPS_WORD(0xE8BB0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00A01021)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80049324\n"
    ".type func_80049324, @function\n"
    "func_80049324:\n"
    "lwc2 $9, 0x0($a0)\n"
    "lwc2 $10, 0x4($a0)\n"
    "lwc2 $11, 0x8($a0)\n"
    "nop\n"
    ".word 0x4AA00428\n"
    "swc2 $25, 0x0($a1)\n"
    "swc2 $26, 0x4($a1)\n"
    "swc2 $27, 0x8($a1)\n"
    "jr $ra\n"
    "addu $v0, $a1, $zero\n"
    ".size func_80049324, .-func_80049324\n"
    ".set reorder\n"
);
#endif

/* Main-exec range [8004924C,80049274) from the SLUS executable.
 * SHA256(span)=ae4cfe9745644b125bec4219d0660a7608bef37aec1d6cdb3d1e601e1112b0bf.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8890000)
MUSASHI_NATIVE_MIPS_WORD(0xC88A0004)
MUSASHI_NATIVE_MIPS_WORD(0xC88B0008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A4DA412)
MUSASHI_NATIVE_MIPS_WORD(0xE8A90000)
MUSASHI_NATIVE_MIPS_WORD(0xE8AA0004)
MUSASHI_NATIVE_MIPS_WORD(0xE8AB0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004924C\n"
    ".type func_8004924C, @function\n"
    "func_8004924C:\n"
    "lwc2 $9, 0x0($a0)\n"
    "lwc2 $10, 0x4($a0)\n"
    "lwc2 $11, 0x8($a0)\n"
    "nop\n"
    ".word 0x4A4DA412\n"
    "swc2 $9, 0x0($a1)\n"
    "swc2 $10, 0x4($a1)\n"
    "swc2 $11, 0x8($a1)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004924C, .-func_8004924C\n"
    ".set reorder\n"
);
#endif

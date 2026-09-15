/* Main-exec range [8004929C,800492D8) from the SLUS executable.
 * SHA256(span)=8e8ac1471c4c2028fb131b2ff67671b6d725c3169d777b44d4b717c2295a0563.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8940000)
MUSASHI_NATIVE_MIPS_WORD(0xC8B50000)
MUSASHI_NATIVE_MIPS_WORD(0xC8D60000)
MUSASHI_NATIVE_MIPS_WORD(0xC8C60000)
MUSASHI_NATIVE_MIPS_WORD(0x48874000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4AF8002A)
MUSASHI_NATIVE_MIPS_WORD(0x8FA80010)
MUSASHI_NATIVE_MIPS_WORD(0x8FA90014)
MUSASHI_NATIVE_MIPS_WORD(0x8FAA0018)
MUSASHI_NATIVE_MIPS_WORD(0xE9140000)
MUSASHI_NATIVE_MIPS_WORD(0xE9350000)
MUSASHI_NATIVE_MIPS_WORD(0xE9560000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004929C\n"
    ".type func_8004929C, @function\n"
    "func_8004929C:\n"
    "lwc2 $20, 0x0($a0)\n"
    "lwc2 $21, 0x0($a1)\n"
    "lwc2 $22, 0x0($a2)\n"
    "lwc2 $6, 0x0($a2)\n"
    "mtc2 $a3, $8\n"
    "nop\n"
    ".word 0x4AF8002A\n"
    "lw $t0, 0x10($sp)\n"
    "lw $t1, 0x14($sp)\n"
    "lw $t2, 0x18($sp)\n"
    "swc2 $20, 0x0($t0)\n"
    "swc2 $21, 0x0($t1)\n"
    "swc2 $22, 0x0($t2)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004929C, .-func_8004929C\n"
    ".set reorder\n"
);
#endif

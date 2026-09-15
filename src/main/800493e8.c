/* Main-exec range [800493E8,80049440) from the SLUS executable.
 * SHA256(span)=b0df3db5528e30315b774c82d909799911f21a661fc9d23bf7ce2dbb33ef3f53.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x484D0000)
MUSASHI_NATIVE_MIPS_WORD(0x484E1000)
MUSASHI_NATIVE_MIPS_WORD(0x484F2000)
MUSASHI_NATIVE_MIPS_WORD(0x8C880000)
MUSASHI_NATIVE_MIPS_WORD(0x8C890004)
MUSASHI_NATIVE_MIPS_WORD(0x8C8A0008)
MUSASHI_NATIVE_MIPS_WORD(0x48C80000)
MUSASHI_NATIVE_MIPS_WORD(0x48C91000)
MUSASHI_NATIVE_MIPS_WORD(0x48CA2000)
MUSASHI_NATIVE_MIPS_WORD(0xC8AB0008)
MUSASHI_NATIVE_MIPS_WORD(0xC8A90000)
MUSASHI_NATIVE_MIPS_WORD(0xC8AA0004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4B70000C)
MUSASHI_NATIVE_MIPS_WORD(0xE8D90000)
MUSASHI_NATIVE_MIPS_WORD(0xE8DA0004)
MUSASHI_NATIVE_MIPS_WORD(0xE8DB0008)
MUSASHI_NATIVE_MIPS_WORD(0x48CD0000)
MUSASHI_NATIVE_MIPS_WORD(0x48CE1000)
MUSASHI_NATIVE_MIPS_WORD(0x48CF2000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800493E8\n"
    ".type func_800493E8, @function\n"
    "func_800493E8:\n"
    "cfc2 $t5, $0\n"
    "cfc2 $t6, $2\n"
    "cfc2 $t7, $4\n"
    "lw $t0, 0x0($a0)\n"
    "lw $t1, 0x4($a0)\n"
    "lw $t2, 0x8($a0)\n"
    "ctc2 $t0, $0\n"
    "ctc2 $t1, $2\n"
    "ctc2 $t2, $4\n"
    "lwc2 $11, 0x8($a1)\n"
    "lwc2 $9, 0x0($a1)\n"
    "lwc2 $10, 0x4($a1)\n"
    "nop\n"
    ".word 0x4B70000C\n"
    "swc2 $25, 0x0($a2)\n"
    "swc2 $26, 0x4($a2)\n"
    "swc2 $27, 0x8($a2)\n"
    "ctc2 $t5, $0\n"
    "ctc2 $t6, $2\n"
    "ctc2 $t7, $4\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800493E8, .-func_800493E8\n"
    ".set reorder\n"
);
#endif

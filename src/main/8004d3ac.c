/* Main-exec range [8004D3AC,8004D420) from the SLUS executable.
 * SHA256(span)=e6d11b474e01720fb02be9c266a08f45b3f830692bf7fd1cddc0d7b7381e3eea.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x484B2800)
MUSASHI_NATIVE_MIPS_WORD(0x484C3000)
MUSASHI_NATIVE_MIPS_WORD(0x484D3800)
MUSASHI_NATIVE_MIPS_WORD(0x48C02800)
MUSASHI_NATIVE_MIPS_WORD(0x48C03000)
MUSASHI_NATIVE_MIPS_WORD(0x48C03800)
MUSASHI_NATIVE_MIPS_WORD(0x84880000)
MUSASHI_NATIVE_MIPS_WORD(0x84890002)
MUSASHI_NATIVE_MIPS_WORD(0x848A0004)
MUSASHI_NATIVE_MIPS_WORD(0x010B4020)
MUSASHI_NATIVE_MIPS_WORD(0x012C4820)
MUSASHI_NATIVE_MIPS_WORD(0x014D5020)
MUSASHI_NATIVE_MIPS_WORD(0x3108FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00094C00)
MUSASHI_NATIVE_MIPS_WORD(0x01284825)
MUSASHI_NATIVE_MIPS_WORD(0x48890000)
MUSASHI_NATIVE_MIPS_WORD(0x488A0800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A180001)
MUSASHI_NATIVE_MIPS_WORD(0xE8AE0000)
MUSASHI_NATIVE_MIPS_WORD(0xE8C80000)
MUSASHI_NATIVE_MIPS_WORD(0x4843F800)
MUSASHI_NATIVE_MIPS_WORD(0x48029800)
MUSASHI_NATIVE_MIPS_WORD(0x48CB2800)
MUSASHI_NATIVE_MIPS_WORD(0x48CC3000)
MUSASHI_NATIVE_MIPS_WORD(0x48CD3800)
MUSASHI_NATIVE_MIPS_WORD(0xACE30000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00021083)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004D3AC\n"
    ".type func_8004D3AC, @function\n"
    "func_8004D3AC:\n"
    "cfc2 $t3, $5\n"
    "cfc2 $t4, $6\n"
    "cfc2 $t5, $7\n"
    "ctc2 $zero, $5\n"
    "ctc2 $zero, $6\n"
    "ctc2 $zero, $7\n"
    "lh $t0, 0x0($a0)\n"
    "lh $t1, 0x2($a0)\n"
    "lh $t2, 0x4($a0)\n"
    "add $t0, $t0, $t3\n"
    "add $t1, $t1, $t4\n"
    "add $t2, $t2, $t5\n"
    "andi $t0, $t0, 0xFFFF\n"
    "sll $t1, $t1, 16\n"
    "or $t1, $t1, $t0\n"
    "mtc2 $t1, $0\n"
    "mtc2 $t2, $1\n"
    "nop\n"
    ".word 0x4A180001\n"
    "swc2 $14, 0x0($a1)\n"
    "swc2 $8, 0x0($a2)\n"
    "cfc2 $v1, $31\n"
    "mfc2 $v0, $19\n"
    "ctc2 $t3, $5\n"
    "ctc2 $t4, $6\n"
    "ctc2 $t5, $7\n"
    "sw $v1, 0x0($a3)\n"
    "jr $ra\n"
    "sra $v0, $v0, 2\n"
    ".size func_8004D3AC, .-func_8004D3AC\n"
    ".set reorder\n"
);
#endif

/* Main-exec range [800480EC,80048180) from the SLUS executable.
 * SHA256(span)=37d46520ff77be803c8c2abd9f2b407b77b1e8686c07420465ec67ba09eb470c.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x4884F000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4802F800)
MUSASHI_NATIVE_MIPS_WORD(0x24010020)
MUSASHI_NATIVE_MIPS_WORD(0x1041001D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30480001)
MUSASHI_NATIVE_MIPS_WORD(0x240AFFFE)
MUSASHI_NATIVE_MIPS_WORD(0x004A5024)
MUSASHI_NATIVE_MIPS_WORD(0x24090013)
MUSASHI_NATIVE_MIPS_WORD(0x012A4822)
MUSASHI_NATIVE_MIPS_WORD(0x00094843)
MUSASHI_NATIVE_MIPS_WORD(0x214BFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x05600003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x01646004)
MUSASHI_NATIVE_MIPS_WORD(0x10000003)
MUSASHI_NATIVE_MIPS_WORD(0x240B0018)
MUSASHI_NATIVE_MIPS_WORD(0x016A5822)
MUSASHI_NATIVE_MIPS_WORD(0x01646007)
MUSASHI_NATIVE_MIPS_WORD(0x218CFFC0)
MUSASHI_NATIVE_MIPS_WORD(0x000C6040)
MUSASHI_NATIVE_MIPS_WORD(0x3C0D8007)
MUSASHI_NATIVE_MIPS_WORD(0x01AC6821)
MUSASHI_NATIVE_MIPS_WORD(0x85ADD8EC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x05200004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x012D1004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00094822)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x012D1006)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x24020000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800480EC\n"
    ".type func_800480EC, @function\n"
    "func_800480EC:\n"
    "mtc2 $a0, $30\n"
    "nop\n"
    "nop\n"
    "mfc2 $v0, $31\n"
    "addiu $at, $zero, 0x20\n"
    ".word 0x1041001D\n"
    "nop\n"
    "andi $t0, $v0, 0x1\n"
    "addiu $t2, $zero, -0x2\n"
    "and $t2, $v0, $t2\n"
    "addiu $t1, $zero, 0x13\n"
    "sub $t1, $t1, $t2\n"
    "sra $t1, $t1, 1\n"
    "addi $t3, $t2, -0x18\n"
    ".word 0x05600003\n"
    "nop\n"
    "sllv $t4, $a0, $t3\n"
    ".word 0x10000003\n"
    ".L80048134:\n"
    "addiu $t3, $zero, 0x18\n"
    "sub $t3, $t3, $t2\n"
    "srav $t4, $a0, $t3\n"
    ".L80048140:\n"
    "addi $t4, $t4, -0x40\n"
    "sll $t4, $t4, 1\n"
    "lui $t5, %hi(D_8006D8EC)\n"
    "addu $t5, $t5, $t4\n"
    "lh $t5, %lo(D_8006D8EC)($t5)\n"
    "nop\n"
    ".word 0x05200004\n"
    "nop\n"
    "sllv $v0, $t5, $t1\n"
    "jr $ra\n"
    "nop\n"
    ".L8004816C:\n"
    "neg $t1, $t1\n"
    "jr $ra\n"
    "srlv $v0, $t5, $t1\n"
    ".L80048178:\n"
    "jr $ra\n"
    "addiu $v0, $zero, 0x0\n"
    ".size func_800480EC, .-func_800480EC\n"
    ".set reorder\n"
);
#endif

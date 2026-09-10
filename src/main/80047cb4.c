/* Exact retail word export for [80047CB4,80047D34); EXE/asm verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c018007)
MUSASHI_NATIVE_MIPS_WORD(0xac3fd8dc)
MUSASHI_NATIVE_MIPS_WORD(0x0c01345b)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3c1f8007)
MUSASHI_NATIVE_MIPS_WORD(0x8fffd8dc)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x40026000)
MUSASHI_NATIVE_MIPS_WORD(0x3c034000)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0x40826000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24080155)
MUSASHI_NATIVE_MIPS_WORD(0x48c8e800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24080100)
MUSASHI_NATIVE_MIPS_WORD(0x48c8f000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x240803e8)
MUSASHI_NATIVE_MIPS_WORD(0x48c8d000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2408ef9e)
MUSASHI_NATIVE_MIPS_WORD(0x48c8d800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3c080140)
MUSASHI_NATIVE_MIPS_WORD(0x48c8e000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x48c0c000)
MUSASHI_NATIVE_MIPS_WORD(0x48c0c800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80047CB4\n"
    ".type func_80047CB4, @function\n"
    "func_80047CB4:\n"
    "lui $at, %hi(D_8006D8DC)\n"
    "sw $ra, %lo(D_8006D8DC)($at)\n"
    ".word 0x0C01345B\n"
    "nop\n"
    "lui $ra, %hi(D_8006D8DC)\n"
    "lw $ra, %lo(D_8006D8DC)($ra)\n"
    "nop\n"
    "mfc0 $v0, $12\n"
    "lui $v1, (0x40000000 >> 16)\n"
    "or $v0, $v0, $v1\n"
    "mtc0 $v0, $12\n"
    "nop\n"
    "addiu $t0, $zero, 0x155\n"
    "ctc2 $t0, $29\n"
    "nop\n"
    "addiu $t0, $zero, 0x100\n"
    "ctc2 $t0, $30\n"
    "nop\n"
    "addiu $t0, $zero, 0x3E8\n"
    "ctc2 $t0, $26\n"
    "nop\n"
    "addiu $t0, $zero, -0x1062\n"
    "ctc2 $t0, $27\n"
    "nop\n"
    "lui $t0, (0x1400000 >> 16)\n"
    "ctc2 $t0, $28\n"
    "nop\n"
    "ctc2 $zero, $24\n"
    "ctc2 $zero, $25\n"
    "nop\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80047CB4, .-func_80047CB4\n"
    ".set reorder\n"
);
#endif

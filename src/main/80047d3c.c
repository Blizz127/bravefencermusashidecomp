/* Exact retail word export for [80047D3C,80047DC0); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x4884f000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4802f800)
MUSASHI_NATIVE_MIPS_WORD(0x24010020)
MUSASHI_NATIVE_MIPS_WORD(0x10410019)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30480001)
MUSASHI_NATIVE_MIPS_WORD(0x240afffe)
MUSASHI_NATIVE_MIPS_WORD(0x004a5024)
MUSASHI_NATIVE_MIPS_WORD(0x2409001f)
MUSASHI_NATIVE_MIPS_WORD(0x012a4822)
MUSASHI_NATIVE_MIPS_WORD(0x00094843)
MUSASHI_NATIVE_MIPS_WORD(0x214bffe8)
MUSASHI_NATIVE_MIPS_WORD(0x05600003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x01646004)
MUSASHI_NATIVE_MIPS_WORD(0x10000003)
MUSASHI_NATIVE_MIPS_WORD(0x240b0018)
MUSASHI_NATIVE_MIPS_WORD(0x016a5822)
MUSASHI_NATIVE_MIPS_WORD(0x01646007)
MUSASHI_NATIVE_MIPS_WORD(0x218cffc0)
MUSASHI_NATIVE_MIPS_WORD(0x000c6040)
MUSASHI_NATIVE_MIPS_WORD(0x3c0d8007)
MUSASHI_NATIVE_MIPS_WORD(0x01ac6821)
MUSASHI_NATIVE_MIPS_WORD(0x85add8ec)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x012d6804)
MUSASHI_NATIVE_MIPS_WORD(0x000d1302)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x24020000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80047D3C\n"
    ".type func_80047D3C, @function\n"
    "func_80047D3C:\n"
    "mtc2 $a0, $30\n"
    "nop\n"
    "nop\n"
    "mfc2 $v0, $31\n"
    "addiu $at, $zero, 0x20\n"
    ".word 0x10410019\n"
    "nop\n"
    "andi $t0, $v0, 0x1\n"
    "addiu $t2, $zero, -0x2\n"
    "and $t2, $v0, $t2\n"
    "addiu $t1, $zero, 0x1F\n"
    "sub $t1, $t1, $t2\n"
    "sra $t1, $t1, 1\n"
    "addi $t3, $t2, -0x18\n"
    ".word 0x05600003\n"
    "nop\n"
    "sllv $t4, $a0, $t3\n"
    ".word 0x10000003\n"
    ".L80047D84:\n"
    "addiu $t3, $zero, 0x18\n"
    "sub $t3, $t3, $t2\n"
    "srav $t4, $a0, $t3\n"
    ".L80047D90:\n"
    "addi $t4, $t4, -0x40\n"
    "sll $t4, $t4, 1\n"
    "lui $t5, %hi(D_8006D8EC)\n"
    "addu $t5, $t5, $t4\n"
    "lh $t5, %lo(D_8006D8EC)($t5)\n"
    "nop\n"
    "sllv $t5, $t5, $t1\n"
    "srl $v0, $t5, 12\n"
    "jr $ra\n"
    "nop\n"
    ".L80047DB8:\n"
    "jr $ra\n"
    "addiu $v0, $zero, 0x0\n"
    ".size func_80047D3C, .-func_80047D3C\n"
    ".set reorder\n"
);
#endif

/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013E194,8013E22C).
 * Offset 0x1603C at overlay base 80128158. SHA256(span)=6055b11a6fb4d8ff853ece661cad65a2dd9e22174d1dd6d54553cf1899173d3f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8013e194.c (recovery=assembly, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFC8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0030)
MUSASHI_NATIVE_MIPS_WORD(0x84820000)
MUSASHI_NATIVE_MIPS_WORD(0x84A30000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20010)
MUSASHI_NATIVE_MIPS_WORD(0x84820002)
MUSASHI_NATIVE_MIPS_WORD(0x84A30002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20014)
MUSASHI_NATIVE_MIPS_WORD(0x84820004)
MUSASHI_NATIVE_MIPS_WORD(0x84A30004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20018)
MUSASHI_NATIVE_MIPS_WORD(0x27A20010)
MUSASHI_NATIVE_MIPS_WORD(0xC8490000)
MUSASHI_NATIVE_MIPS_WORD(0xC84A0004)
MUSASHI_NATIVE_MIPS_WORD(0xC84B0008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4AA80428)
MUSASHI_NATIVE_MIPS_WORD(0x27A20020)
MUSASHI_NATIVE_MIPS_WORD(0xE8590000)
MUSASHI_NATIVE_MIPS_WORD(0xE85A0004)
MUSASHI_NATIVE_MIPS_WORD(0xE85B0008)
MUSASHI_NATIVE_MIPS_WORD(0x8FA40020)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20024)
MUSASHI_NATIVE_MIPS_WORD(0x8FA30028)
MUSASHI_NATIVE_MIPS_WORD(0x00822021)
MUSASHI_NATIVE_MIPS_WORD(0x0C01203B)
MUSASHI_NATIVE_MIPS_WORD(0x00832021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0030)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0038)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8013E194\n"
    ".type func_8013E194, @function\n"
    "func_8013E194:\n"
    "addiu $sp, $sp, -0x38\n"
    "sw $ra, 0x30($sp)\n"
    "lh $v0, 0x0($a0)\n"
    "lh $v1, 0x0($a1)\n"
    "nop\n"
    "subu $v0, $v0, $v1\n"
    "sw $v0, 0x10($sp)\n"
    "lh $v0, 0x2($a0)\n"
    "lh $v1, 0x2($a1)\n"
    "nop\n"
    "subu $v0, $v0, $v1\n"
    "sw $v0, 0x14($sp)\n"
    "lh $v0, 0x4($a0)\n"
    "lh $v1, 0x4($a1)\n"
    "nop\n"
    "subu $v0, $v0, $v1\n"
    "sw $v0, 0x18($sp)\n"
    "addiu $v0, $sp, 0x10\n"
    "lwc2 $9, 0x0($v0)\n"
    "lwc2 $10, 0x4($v0)\n"
    "lwc2 $11, 0x8($v0)\n"
    "nop\n"
    "nop\n"
    ".word 0x4AA80428\n"
    "addiu $v0, $sp, 0x20\n"
    "swc2 $25, 0x0($v0)\n"
    "swc2 $26, 0x4($v0)\n"
    "swc2 $27, 0x8($v0)\n"
    "lw $a0, 0x20($sp)\n"
    "lw $v0, 0x24($sp)\n"
    "lw $v1, 0x28($sp)\n"
    "addu $a0, $a0, $v0\n"
    ".word 0x0C01203B\n"
    "addu $a0, $a0, $v1\n"
    "lw $ra, 0x30($sp)\n"
    "addiu $sp, $sp, 0x38\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8013E194, .-func_8013E194\n"
    ".set reorder\n"
);
#endif

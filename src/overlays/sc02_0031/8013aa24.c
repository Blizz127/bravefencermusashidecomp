/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013AA24,8013AB54).
 * Offset 0x128CC at overlay base 80128158. SHA256(span)=cbd7e59faae1d3e84f3e304b97effb6829815cbdcdc03f72d431bc4eb3c4b381.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8013aa24.c (recovery=assembly, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFEF8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB000F0)
MUSASHI_NATIVE_MIPS_WORD(0x00A08021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0100)
MUSASHI_NATIVE_MIPS_WORD(0xAFB300FC)
MUSASHI_NATIVE_MIPS_WORD(0xAFB200F8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB100F4)
MUSASHI_NATIVE_MIPS_WORD(0x96020008)
MUSASHI_NATIVE_MIPS_WORD(0x00809021)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00012)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00014)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00016)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x9603000A)
MUSASHI_NATIVE_MIPS_WORD(0x24021000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A0001A)
MUSASHI_NATIVE_MIPS_WORD(0xA7A0001C)
MUSASHI_NATIVE_MIPS_WORD(0xA7A0001E)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20020)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30018)
MUSASHI_NATIVE_MIPS_WORD(0x86420024)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20024)
MUSASHI_NATIVE_MIPS_WORD(0x86420026)
MUSASHI_NATIVE_MIPS_WORD(0xAFA0002C)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20028)
MUSASHI_NATIVE_MIPS_WORD(0x27A20010)
MUSASHI_NATIVE_MIPS_WORD(0x8C4C0000)
MUSASHI_NATIVE_MIPS_WORD(0x8C4D0004)
MUSASHI_NATIVE_MIPS_WORD(0x48CC0000)
MUSASHI_NATIVE_MIPS_WORD(0x48CD0800)
MUSASHI_NATIVE_MIPS_WORD(0x8C4C0008)
MUSASHI_NATIVE_MIPS_WORD(0x8C4D000C)
MUSASHI_NATIVE_MIPS_WORD(0x8C4E0010)
MUSASHI_NATIVE_MIPS_WORD(0x48CC1000)
MUSASHI_NATIVE_MIPS_WORD(0x48CD1800)
MUSASHI_NATIVE_MIPS_WORD(0x48CE2000)
MUSASHI_NATIVE_MIPS_WORD(0x8C4C0014)
MUSASHI_NATIVE_MIPS_WORD(0x8C4D0018)
MUSASHI_NATIVE_MIPS_WORD(0x48CC2800)
MUSASHI_NATIVE_MIPS_WORD(0x8C4E001C)
MUSASHI_NATIVE_MIPS_WORD(0x48CD3000)
MUSASHI_NATIVE_MIPS_WORD(0x48CE3800)
MUSASHI_NATIVE_MIPS_WORD(0x26040008)
MUSASHI_NATIVE_MIPS_WORD(0x27B30030)
MUSASHI_NATIVE_MIPS_WORD(0x02603021)
MUSASHI_NATIVE_MIPS_WORD(0x27B100B0)
MUSASHI_NATIVE_MIPS_WORD(0x8605000C)
MUSASHI_NATIVE_MIPS_WORD(0x0C04EB4E)
MUSASHI_NATIVE_MIPS_WORD(0x02203821)
MUSASHI_NATIVE_MIPS_WORD(0x02402021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04EC81)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x26450024)
MUSASHI_NATIVE_MIPS_WORD(0x02603021)
MUSASHI_NATIVE_MIPS_WORD(0x02203821)
MUSASHI_NATIVE_MIPS_WORD(0x3C03800C)
MUSASHI_NATIVE_MIPS_WORD(0x94639A02)
MUSASHI_NATIVE_MIPS_WORD(0x9644001A)
MUSASHI_NATIVE_MIPS_WORD(0x00031080)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C22651C)
MUSASHI_NATIVE_MIPS_WORD(0x00042080)
MUSASHI_NATIVE_MIPS_WORD(0x0C04EBC8)
MUSASHI_NATIVE_MIPS_WORD(0x00442021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0100)
MUSASHI_NATIVE_MIPS_WORD(0x8FB300FC)
MUSASHI_NATIVE_MIPS_WORD(0x8FB200F8)
MUSASHI_NATIVE_MIPS_WORD(0x8FB100F4)
MUSASHI_NATIVE_MIPS_WORD(0x8FB000F0)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0108)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8013AA24\n"
    ".type func_8013AA24, @function\n"
    "func_8013AA24:\n"
    "addiu $sp, $sp, -0x108\n"
    "sw $s0, 0xF0($sp)\n"
    "addu $s0, $a1, $zero\n"
    "sw $ra, 0x100($sp)\n"
    "sw $s3, 0xFC($sp)\n"
    "sw $s2, 0xF8($sp)\n"
    "sw $s1, 0xF4($sp)\n"
    "lhu $v0, 0x8($s0)\n"
    "addu $s2, $a0, $zero\n"
    "sh $zero, 0x12($sp)\n"
    "sh $zero, 0x14($sp)\n"
    "sh $zero, 0x16($sp)\n"
    "sh $v0, 0x10($sp)\n"
    "lhu $v1, 0xA($s0)\n"
    "addiu $v0, $zero, 0x1000\n"
    "sh $zero, 0x1A($sp)\n"
    "sh $zero, 0x1C($sp)\n"
    "sh $zero, 0x1E($sp)\n"
    "sh $v0, 0x20($sp)\n"
    "sh $v1, 0x18($sp)\n"
    "lh $v0, 0x24($s2)\n"
    "nop\n"
    "sw $v0, 0x24($sp)\n"
    "lh $v0, 0x26($s2)\n"
    "sw $zero, 0x2C($sp)\n"
    "sw $v0, 0x28($sp)\n"
    "addiu $v0, $sp, 0x10\n"
    "lw $t4, 0x0($v0)\n"
    "lw $t5, 0x4($v0)\n"
    "ctc2 $t4, $0\n"
    "ctc2 $t5, $1\n"
    "lw $t4, 0x8($v0)\n"
    "lw $t5, 0xC($v0)\n"
    "lw $t6, 0x10($v0)\n"
    "ctc2 $t4, $2\n"
    "ctc2 $t5, $3\n"
    "ctc2 $t6, $4\n"
    "lw $t4, 0x14($v0)\n"
    "lw $t5, 0x18($v0)\n"
    "ctc2 $t4, $5\n"
    "lw $t6, 0x1C($v0)\n"
    "ctc2 $t5, $6\n"
    "ctc2 $t6, $7\n"
    "addiu $a0, $s0, 0x8\n"
    "addiu $s3, $sp, 0x30\n"
    "addu $a2, $s3, $zero\n"
    "addiu $s1, $sp, 0xB0\n"
    "lh $a1, 0xC($s0)\n"
    ".word 0x0C04EB4E\n"
    "addu $a3, $s1, $zero\n"
    "addu $a0, $s2, $zero\n"
    ".word 0x0C04EC81\n"
    "addu $a1, $s0, $zero\n"
    "addiu $a1, $s2, 0x24\n"
    "addu $a2, $s3, $zero\n"
    "addu $a3, $s1, $zero\n"
    "lui $v1, %hi(D_800B9A02)\n"
    "lhu $v1, %lo(D_800B9A02)($v1)\n"
    "lhu $a0, 0x1A($s2)\n"
    "sll $v0, $v1, 2\n"
    "addu $v0, $v0, $v1\n"
    "sll $v0, $v0, 2\n"
    "lui $at, %hi(D_800A651C)\n"
    "addu $at, $at, $v0\n"
    "lw $v0, %lo(D_800A651C)($at)\n"
    "sll $a0, $a0, 2\n"
    ".word 0x0C04EBC8\n"
    "addu $a0, $v0, $a0\n"
    "lw $ra, 0x100($sp)\n"
    "lw $s3, 0xFC($sp)\n"
    "lw $s2, 0xF8($sp)\n"
    "lw $s1, 0xF4($sp)\n"
    "lw $s0, 0xF0($sp)\n"
    "addiu $sp, $sp, 0x108\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8013AA24, .-func_8013AA24\n"
    ".set reorder\n"
);
#endif

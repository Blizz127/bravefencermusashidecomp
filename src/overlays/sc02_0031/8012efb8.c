/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012EFB8,8012F038).
 * Offset 0x6E60 at overlay base 80128158. SHA256(span)=71592d38d0f50c89e6e0257af924fa13409ad992a259c0e67b2a3bc5bb68fdef.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012efb8.c (recovery=assembly, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800B)
MUSASHI_NATIVE_MIPS_WORD(0x2442F648)
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
MUSASHI_NATIVE_MIPS_WORD(0xC8800000)
MUSASHI_NATIVE_MIPS_WORD(0xC8810004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A180001)
MUSASHI_NATIVE_MIPS_WORD(0xE8AE0000)
MUSASHI_NATIVE_MIPS_WORD(0x484CF800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAFAC0000)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20000)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8012EFB8\n"
    ".type func_8012EFB8, @function\n"
    "func_8012EFB8:\n"
    "addiu $sp, $sp, -0x8\n"
    "lui $v0, %hi(D_800AF648)\n"
    "addiu $v0, $v0, %lo(D_800AF648)\n"
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
    "lwc2 $0, 0x0($a0)\n"
    "lwc2 $1, 0x4($a0)\n"
    "nop\n"
    "nop\n"
    ".word 0x4A180001\n"
    "swc2 $14, 0x0($a1)\n"
    "cfc2 $t4, $31\n"
    "nop\n"
    "sw $t4, 0x0($sp)\n"
    "lw $v0, 0x0($sp)\n"
    "addiu $sp, $sp, 0x8\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8012EFB8, .-func_8012EFB8\n"
    ".set reorder\n"
);
#endif

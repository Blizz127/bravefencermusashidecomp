/* Main-exec range [80013478,800134FC) from the SLUS executable.
 * SHA256(span)=e2c8c38c18ad38c2518173ec2be1b847af6c7edd191978bad43931e4f157868f.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x84820002)
MUSASHI_NATIVE_MIPS_WORD(0x84A30000)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20000)
MUSASHI_NATIVE_MIPS_WORD(0x84820006)
MUSASHI_NATIVE_MIPS_WORD(0x84A30002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20004)
MUSASHI_NATIVE_MIPS_WORD(0x8482000A)
MUSASHI_NATIVE_MIPS_WORD(0x84A30004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20008)
MUSASHI_NATIVE_MIPS_WORD(0xCBA90000)
MUSASHI_NATIVE_MIPS_WORD(0xCBAA0004)
MUSASHI_NATIVE_MIPS_WORD(0xCBAB0008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4AA00428)
MUSASHI_NATIVE_MIPS_WORD(0x27A20010)
MUSASHI_NATIVE_MIPS_WORD(0xE8590000)
MUSASHI_NATIVE_MIPS_WORD(0xE85A0004)
MUSASHI_NATIVE_MIPS_WORD(0xE85B0008)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20010)
MUSASHI_NATIVE_MIPS_WORD(0x8FA30014)
MUSASHI_NATIVE_MIPS_WORD(0x8FA40018)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80013478\n"
    ".type func_80013478, @function\n"
    "func_80013478:\n"
    "lh $v0, 0x2($a0)\n"
    "lh $v1, 0x0($a1)\n"
    "addiu $sp, $sp, -0x20\n"
    "subu $v0, $v0, $v1\n"
    "sw $v0, 0x0($sp)\n"
    "lh $v0, 0x6($a0)\n"
    "lh $v1, 0x2($a1)\n"
    "nop\n"
    "subu $v0, $v0, $v1\n"
    "sw $v0, 0x4($sp)\n"
    "lh $v0, 0xA($a0)\n"
    "lh $v1, 0x4($a1)\n"
    "nop\n"
    "subu $v0, $v0, $v1\n"
    "sw $v0, 0x8($sp)\n"
    "lwc2 $9, 0x0($sp)\n"
    "lwc2 $10, 0x4($sp)\n"
    "lwc2 $11, 0x8($sp)\n"
    "nop\n"
    "nop\n"
    ".word 0x4AA00428\n"
    "addiu $v0, $sp, 0x10\n"
    "swc2 $25, 0x0($v0)\n"
    "swc2 $26, 0x4($v0)\n"
    "swc2 $27, 0x8($v0)\n"
    "lw $v0, 0x10($sp)\n"
    "lw $v1, 0x14($sp)\n"
    "lw $a0, 0x18($sp)\n"
    "addu $v0, $v0, $v1\n"
    "addu $v0, $v0, $a0\n"
    "addiu $sp, $sp, 0x20\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80013478, .-func_80013478\n"
    ".set reorder\n"
);
#endif

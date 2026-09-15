/* Main-exec range [8004867C,8004871C) from the SLUS executable.
 * SHA256(span)=4295fbe0dfe23cc7c10d0e0ad997b52fe30604b3a3dd09b5197d3a9bba2dc881.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C0E8007)
MUSASHI_NATIVE_MIPS_WORD(0x8DCEDC18)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x29C10280)
MUSASHI_NATIVE_MIPS_WORD(0x1420000A)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC3FDC0C)
MUSASHI_NATIVE_MIPS_WORD(0x3C048007)
MUSASHI_NATIVE_MIPS_WORD(0x0C017181)
MUSASHI_NATIVE_MIPS_WORD(0x2484DE9C)
MUSASHI_NATIVE_MIPS_WORD(0x3C1F8007)
MUSASHI_NATIVE_MIPS_WORD(0x8FFFDC0C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C0F8007)
MUSASHI_NATIVE_MIPS_WORD(0x01EE7821)
MUSASHI_NATIVE_MIPS_WORD(0x25EFDC1C)
MUSASHI_NATIVE_MIPS_WORD(0x48480000)
MUSASHI_NATIVE_MIPS_WORD(0x48490800)
MUSASHI_NATIVE_MIPS_WORD(0xADE80000)
MUSASHI_NATIVE_MIPS_WORD(0xADE90004)
MUSASHI_NATIVE_MIPS_WORD(0x48481000)
MUSASHI_NATIVE_MIPS_WORD(0x48491800)
MUSASHI_NATIVE_MIPS_WORD(0xADE80008)
MUSASHI_NATIVE_MIPS_WORD(0xADE9000C)
MUSASHI_NATIVE_MIPS_WORD(0x48482000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xADE80010)
MUSASHI_NATIVE_MIPS_WORD(0x48482800)
MUSASHI_NATIVE_MIPS_WORD(0x48493000)
MUSASHI_NATIVE_MIPS_WORD(0x484A3800)
MUSASHI_NATIVE_MIPS_WORD(0xADE80014)
MUSASHI_NATIVE_MIPS_WORD(0xADE90018)
MUSASHI_NATIVE_MIPS_WORD(0xADEA001C)
MUSASHI_NATIVE_MIPS_WORD(0x21CE0020)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC2EDC18)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004867C\n"
    ".type func_8004867C, @function\n"
    "func_8004867C:\n"
    "lui $t6, %hi(D_8006DC18)\n"
    "lw $t6, %lo(D_8006DC18)($t6)\n"
    "nop\n"
    "slti $at, $t6, 0x280\n"
    ".word 0x1420000A\n"
    "lui $at, %hi(D_8006DC0C)\n"
    "sw $ra, %lo(D_8006DC0C)($at)\n"
    "lui $a0, %hi(D_8006DE9C)\n"
    ".word 0x0C017181\n"
    "addiu $a0, $a0, %lo(D_8006DE9C)\n"
    "lui $ra, %hi(D_8006DC0C)\n"
    "lw $ra, %lo(D_8006DC0C)($ra)\n"
    "nop\n"
    "jr $ra\n"
    "nop\n"
    ".L800486B8:\n"
    "lui $t7, %hi(D_8006DC1C)\n"
    "addu $t7, $t7, $t6\n"
    "addiu $t7, $t7, %lo(D_8006DC1C)\n"
    "cfc2 $t0, $0\n"
    "cfc2 $t1, $1\n"
    "sw $t0, 0x0($t7)\n"
    "sw $t1, 0x4($t7)\n"
    "cfc2 $t0, $2\n"
    "cfc2 $t1, $3\n"
    "sw $t0, 0x8($t7)\n"
    "sw $t1, 0xC($t7)\n"
    "cfc2 $t0, $4\n"
    "nop\n"
    "sw $t0, 0x10($t7)\n"
    "cfc2 $t0, $5\n"
    "cfc2 $t1, $6\n"
    "cfc2 $t2, $7\n"
    "sw $t0, 0x14($t7)\n"
    "sw $t1, 0x18($t7)\n"
    "sw $t2, 0x1C($t7)\n"
    "addi $t6, $t6, 0x20\n"
    "lui $at, %hi(D_8006DC18)\n"
    "sw $t6, %lo(D_8006DC18)($at)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004867C, .-func_8004867C\n"
    ".set reorder\n"
);
#endif

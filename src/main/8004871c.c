/* Main-exec range [8004871C,800487BC) from the SLUS executable.
 * SHA256(span)=6e165c7c14716ed71fe4bed989fd3cf0489f84ba47739fc56dcbd9706df1501a.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C0E8007)
MUSASHI_NATIVE_MIPS_WORD(0x8DCEDC18)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1DC0000A)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC3FDC0C)
MUSASHI_NATIVE_MIPS_WORD(0x3C048007)
MUSASHI_NATIVE_MIPS_WORD(0x0C017181)
MUSASHI_NATIVE_MIPS_WORD(0x2484DECD)
MUSASHI_NATIVE_MIPS_WORD(0x3C1F8007)
MUSASHI_NATIVE_MIPS_WORD(0x8FFFDC0C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x21CEFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC2EDC18)
MUSASHI_NATIVE_MIPS_WORD(0x3C0F8007)
MUSASHI_NATIVE_MIPS_WORD(0x01EE7821)
MUSASHI_NATIVE_MIPS_WORD(0x25EFDC1C)
MUSASHI_NATIVE_MIPS_WORD(0x8DE80000)
MUSASHI_NATIVE_MIPS_WORD(0x8DE90004)
MUSASHI_NATIVE_MIPS_WORD(0x48C80000)
MUSASHI_NATIVE_MIPS_WORD(0x48C90800)
MUSASHI_NATIVE_MIPS_WORD(0x8DE80008)
MUSASHI_NATIVE_MIPS_WORD(0x8DE9000C)
MUSASHI_NATIVE_MIPS_WORD(0x48C81000)
MUSASHI_NATIVE_MIPS_WORD(0x48C91800)
MUSASHI_NATIVE_MIPS_WORD(0x8DE80010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x48C82000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8DE80014)
MUSASHI_NATIVE_MIPS_WORD(0x8DE90018)
MUSASHI_NATIVE_MIPS_WORD(0x8DEA001C)
MUSASHI_NATIVE_MIPS_WORD(0x48C82800)
MUSASHI_NATIVE_MIPS_WORD(0x48C93000)
MUSASHI_NATIVE_MIPS_WORD(0x48CA3800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004871C\n"
    ".type func_8004871C, @function\n"
    "func_8004871C:\n"
    "lui $t6, %hi(D_8006DC18)\n"
    "lw $t6, %lo(D_8006DC18)($t6)\n"
    "nop\n"
    ".word 0x1DC0000A\n"
    "lui $at, %hi(D_8006DC0C)\n"
    "sw $ra, %lo(D_8006DC0C)($at)\n"
    "lui $a0, %hi(D_8006DECD)\n"
    ".word 0x0C017181\n"
    "addiu $a0, $a0, %lo(D_8006DECD)\n"
    "lui $ra, %hi(D_8006DC0C)\n"
    "lw $ra, %lo(D_8006DC0C)($ra)\n"
    "nop\n"
    "jr $ra\n"
    "nop\n"
    ".L80048754:\n"
    "addi $t6, $t6, -0x20\n"
    "lui $at, %hi(D_8006DC18)\n"
    "sw $t6, %lo(D_8006DC18)($at)\n"
    "lui $t7, %hi(D_8006DC1C)\n"
    "addu $t7, $t7, $t6\n"
    "addiu $t7, $t7, %lo(D_8006DC1C)\n"
    "lw $t0, 0x0($t7)\n"
    "lw $t1, 0x4($t7)\n"
    "ctc2 $t0, $0\n"
    "ctc2 $t1, $1\n"
    "lw $t0, 0x8($t7)\n"
    "lw $t1, 0xC($t7)\n"
    "ctc2 $t0, $2\n"
    "ctc2 $t1, $3\n"
    "lw $t0, 0x10($t7)\n"
    "nop\n"
    "ctc2 $t0, $4\n"
    "nop\n"
    "lw $t0, 0x14($t7)\n"
    "lw $t1, 0x18($t7)\n"
    "lw $t2, 0x1C($t7)\n"
    "ctc2 $t0, $5\n"
    "ctc2 $t1, $6\n"
    "ctc2 $t2, $7\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004871C, .-func_8004871C\n"
    ".set reorder\n"
);
#endif

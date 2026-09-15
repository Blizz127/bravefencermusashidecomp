/* Main-exec range [8004D420,8004D504) from the SLUS executable.
 * SHA256(span)=350b12fadac5b2da9ae50dec3db694aedaf72d483f2ac07b208aa68fd158d7da.
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
MUSASHI_NATIVE_MIPS_WORD(0x84AE0000)
MUSASHI_NATIVE_MIPS_WORD(0x84AF0002)
MUSASHI_NATIVE_MIPS_WORD(0x84B80004)
MUSASHI_NATIVE_MIPS_WORD(0x84D90000)
MUSASHI_NATIVE_MIPS_WORD(0x84C20002)
MUSASHI_NATIVE_MIPS_WORD(0x84C30004)
MUSASHI_NATIVE_MIPS_WORD(0x010B4020)
MUSASHI_NATIVE_MIPS_WORD(0x012C4820)
MUSASHI_NATIVE_MIPS_WORD(0x014D5020)
MUSASHI_NATIVE_MIPS_WORD(0x01CB7020)
MUSASHI_NATIVE_MIPS_WORD(0x01EC7820)
MUSASHI_NATIVE_MIPS_WORD(0x030DC020)
MUSASHI_NATIVE_MIPS_WORD(0x032BC820)
MUSASHI_NATIVE_MIPS_WORD(0x004C1020)
MUSASHI_NATIVE_MIPS_WORD(0x006D1820)
MUSASHI_NATIVE_MIPS_WORD(0x3108FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00094C00)
MUSASHI_NATIVE_MIPS_WORD(0x01284825)
MUSASHI_NATIVE_MIPS_WORD(0x31CEFFFF)
MUSASHI_NATIVE_MIPS_WORD(0x000F7C00)
MUSASHI_NATIVE_MIPS_WORD(0x01EE7825)
MUSASHI_NATIVE_MIPS_WORD(0x3339FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00591025)
MUSASHI_NATIVE_MIPS_WORD(0x48890000)
MUSASHI_NATIVE_MIPS_WORD(0x488A0800)
MUSASHI_NATIVE_MIPS_WORD(0x488F1000)
MUSASHI_NATIVE_MIPS_WORD(0x48981800)
MUSASHI_NATIVE_MIPS_WORD(0x48822000)
MUSASHI_NATIVE_MIPS_WORD(0x48832800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A280030)
MUSASHI_NATIVE_MIPS_WORD(0x8FA80010)
MUSASHI_NATIVE_MIPS_WORD(0x8FA90014)
MUSASHI_NATIVE_MIPS_WORD(0x8FAA0018)
MUSASHI_NATIVE_MIPS_WORD(0x8FAE001C)
MUSASHI_NATIVE_MIPS_WORD(0xE8EC0000)
MUSASHI_NATIVE_MIPS_WORD(0xE90D0000)
MUSASHI_NATIVE_MIPS_WORD(0xE92E0000)
MUSASHI_NATIVE_MIPS_WORD(0xE9480000)
MUSASHI_NATIVE_MIPS_WORD(0x4843F800)
MUSASHI_NATIVE_MIPS_WORD(0x48029800)
MUSASHI_NATIVE_MIPS_WORD(0x48CB2800)
MUSASHI_NATIVE_MIPS_WORD(0x48CC3000)
MUSASHI_NATIVE_MIPS_WORD(0x48CD3800)
MUSASHI_NATIVE_MIPS_WORD(0xADC30000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00021083)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004D420\n"
    ".type func_8004D420, @function\n"
    "func_8004D420:\n"
    "cfc2 $t3, $5\n"
    "cfc2 $t4, $6\n"
    "cfc2 $t5, $7\n"
    "ctc2 $zero, $5\n"
    "ctc2 $zero, $6\n"
    "ctc2 $zero, $7\n"
    "lh $t0, 0x0($a0)\n"
    "lh $t1, 0x2($a0)\n"
    "lh $t2, 0x4($a0)\n"
    "lh $t6, 0x0($a1)\n"
    "lh $t7, 0x2($a1)\n"
    "lh $t8, 0x4($a1)\n"
    "lh $t9, 0x0($a2)\n"
    "lh $v0, 0x2($a2)\n"
    "lh $v1, 0x4($a2)\n"
    "add $t0, $t0, $t3\n"
    "add $t1, $t1, $t4\n"
    "add $t2, $t2, $t5\n"
    "add $t6, $t6, $t3\n"
    "add $t7, $t7, $t4\n"
    "add $t8, $t8, $t5\n"
    "add $t9, $t9, $t3\n"
    "add $v0, $v0, $t4\n"
    "add $v1, $v1, $t5\n"
    "andi $t0, $t0, 0xFFFF\n"
    "sll $t1, $t1, 16\n"
    "or $t1, $t1, $t0\n"
    "andi $t6, $t6, 0xFFFF\n"
    "sll $t7, $t7, 16\n"
    "or $t7, $t7, $t6\n"
    "andi $t9, $t9, 0xFFFF\n"
    "sll $v0, $v0, 16\n"
    "or $v0, $v0, $t9\n"
    "mtc2 $t1, $0\n"
    "mtc2 $t2, $1\n"
    "mtc2 $t7, $2\n"
    "mtc2 $t8, $3\n"
    "mtc2 $v0, $4\n"
    "mtc2 $v1, $5\n"
    "nop\n"
    ".word 0x4A280030\n"
    "lw $t0, 0x10($sp)\n"
    "lw $t1, 0x14($sp)\n"
    "lw $t2, 0x18($sp)\n"
    "lw $t6, 0x1C($sp)\n"
    "swc2 $12, 0x0($a3)\n"
    "swc2 $13, 0x0($t0)\n"
    "swc2 $14, 0x0($t1)\n"
    "swc2 $8, 0x0($t2)\n"
    "cfc2 $v1, $31\n"
    "mfc2 $v0, $19\n"
    "ctc2 $t3, $5\n"
    "ctc2 $t4, $6\n"
    "ctc2 $t5, $7\n"
    "sw $v1, 0x0($t6)\n"
    "jr $ra\n"
    "sra $v0, $v0, 2\n"
    ".size func_8004D420, .-func_8004D420\n"
    ".set reorder\n"
);
#endif

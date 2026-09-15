/* Main-exec range [8004806C,800480EC) from the SLUS executable.
 * SHA256(span)=1233aa05dbb33bf9fad4cb52c8a3c6474372d176bd6c83ffe0326f94575766ab.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x000630C0)
MUSASHI_NATIVE_MIPS_WORD(0x00C53020)
MUSASHI_NATIVE_MIPS_WORD(0x48874000)
MUSASHI_NATIVE_MIPS_WORD(0x8CA80000)
MUSASHI_NATIVE_MIPS_WORD(0x84AA0004)
MUSASHI_NATIVE_MIPS_WORD(0x00084C03)
MUSASHI_NATIVE_MIPS_WORD(0x3108FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x48884800)
MUSASHI_NATIVE_MIPS_WORD(0x48895000)
MUSASHI_NATIVE_MIPS_WORD(0x488A5800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4B98003D)
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x84870004)
MUSASHI_NATIVE_MIPS_WORD(0x00021C03)
MUSASHI_NATIVE_MIPS_WORD(0x3042FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x20A50008)
MUSASHI_NATIVE_MIPS_WORD(0x48084800)
MUSASHI_NATIVE_MIPS_WORD(0x48095000)
MUSASHI_NATIVE_MIPS_WORD(0x480A5800)
MUSASHI_NATIVE_MIPS_WORD(0x00481020)
MUSASHI_NATIVE_MIPS_WORD(0x00691820)
MUSASHI_NATIVE_MIPS_WORD(0x00EA3820)
MUSASHI_NATIVE_MIPS_WORD(0xA4820000)
MUSASHI_NATIVE_MIPS_WORD(0xA4830002)
MUSASHI_NATIVE_MIPS_WORD(0xA4870004)
MUSASHI_NATIVE_MIPS_WORD(0x20840008)
MUSASHI_NATIVE_MIPS_WORD(0x14A6FFE6)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004806C\n"
    ".type func_8004806C, @function\n"
    "func_8004806C:\n"
    "sll $a2, $a2, 3\n"
    "add $a2, $a2, $a1\n"
    "mtc2 $a3, $8\n"
    ".L80048078:\n"
    "lw $t0, 0x0($a1)\n"
    "lh $t2, 0x4($a1)\n"
    "sra $t1, $t0, 16\n"
    "andi $t0, $t0, 0xFFFF\n"
    "mtc2 $t0, $9\n"
    "mtc2 $t1, $10\n"
    "mtc2 $t2, $11\n"
    "nop\n"
    "nop\n"
    ".word 0x4B98003D\n"
    "lw $v0, 0x0($a0)\n"
    "lh $a3, 0x4($a0)\n"
    "sra $v1, $v0, 16\n"
    "andi $v0, $v0, 0xFFFF\n"
    "addi $a1, $a1, 0x8\n"
    "mfc2 $t0, $9\n"
    "mfc2 $t1, $10\n"
    "mfc2 $t2, $11\n"
    "add $v0, $v0, $t0\n"
    "add $v1, $v1, $t1\n"
    "add $a3, $a3, $t2\n"
    "sh $v0, 0x0($a0)\n"
    "sh $v1, 0x2($a0)\n"
    "sh $a3, 0x4($a0)\n"
    "addi $a0, $a0, 0x8\n"
    ".word 0x14A6FFE6\n"
    "nop\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004806C, .-func_8004806C\n"
    ".set reorder\n"
);
#endif

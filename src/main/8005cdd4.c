/* Main-exec range [8005CDD4,8005CE10) from the SLUS executable.
 * SHA256(span)=462aefcefbdfb2be0b9b3f695de3a11dc6af6f48163c792ceea2d1ec9334800c.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C9F0000)
MUSASHI_NATIVE_MIPS_WORD(0x8C9C002C)
MUSASHI_NATIVE_MIPS_WORD(0x8C9D0004)
MUSASHI_NATIVE_MIPS_WORD(0x8C9E0008)
MUSASHI_NATIVE_MIPS_WORD(0x8C90000C)
MUSASHI_NATIVE_MIPS_WORD(0x8C910010)
MUSASHI_NATIVE_MIPS_WORD(0x8C920014)
MUSASHI_NATIVE_MIPS_WORD(0x8C930018)
MUSASHI_NATIVE_MIPS_WORD(0x8C94001C)
MUSASHI_NATIVE_MIPS_WORD(0x8C950020)
MUSASHI_NATIVE_MIPS_WORD(0x8C960024)
MUSASHI_NATIVE_MIPS_WORD(0x8C970028)
MUSASHI_NATIVE_MIPS_WORD(0x00A01021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Retail saved-context restore: 48-byte PS1 register record.
 * This source overlay is not a host setjmp/longjmp implementation. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005CDD4\n"
    ".type func_8005CDD4, @function\n"
    "func_8005CDD4:\n"
    "lw $ra,0($a0)\n"
    "lw $gp,44($a0)\n"
    "lw $sp,4($a0)\n"
    "lw $fp,8($a0)\n"
    "lw $s0,12($a0)\n"
    "lw $s1,16($a0)\n"
    "lw $s2,20($a0)\n"
    "lw $s3,24($a0)\n"
    "lw $s4,28($a0)\n"
    "lw $s5,32($a0)\n"
    "lw $s6,36($a0)\n"
    "lw $s7,40($a0)\n"
    "addu $v0,$a1,$zero\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8005CDD4, .-func_8005CDD4\n"
    ".set reorder\n"
);
#endif

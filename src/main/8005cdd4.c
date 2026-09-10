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

#include "psx_types.h"

/* Retail startup service boundary; native service behavior remains unbound. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005CE50\n"
    ".type func_8005CE50, @function\n"
    "func_8005CE50:\n"
    "addiu $t2,$zero,0xA0\n"
    "jr $t2\n"
    "addiu $t1,$zero,0x72\n"
    ".size func_8005CE50, .-func_8005CE50\n"
    ".set reorder\n"
);

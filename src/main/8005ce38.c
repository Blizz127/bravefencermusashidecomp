#include "psx_types.h"

/* Retail startup service boundary; native service behavior remains unbound. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005CE38\n"
    ".type func_8005CE38, @function\n"
    "func_8005CE38:\n"
    "addiu $t2,$zero,0xA0\n"
    "jr $t2\n"
    "addiu $t1,$zero,0x49\n"
    ".size func_8005CE38, .-func_8005CE38\n"
    ".set reorder\n"
);

#include "psx_types.h"

/* Retail startup service boundary; native service behavior remains unbound. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005CEF8\n"
    ".type func_8005CEF8, @function\n"
    "func_8005CEF8:\n"
    "addiu $t2,$zero,0xB0\n"
    "jr $t2\n"
    "addiu $t1,$zero,0x19\n"
    ".size func_8005CEF8, .-func_8005CEF8\n"
    ".set reorder\n"
);

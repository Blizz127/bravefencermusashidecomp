#include "psx_types.h"

/* Retail B0:17 service thunk. Retail observation shows 800427F4 reaches this
 * from its saved-context dispatch path. This is a PS1 ABI boundary, not a
 * native ReturnFromException implementation. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005CED8\n"
    ".type func_8005CED8, @function\n"
    "func_8005CED8:\n"
    "addiu $t2,$zero,0xB0\n"
    "jr $t2\n"
    "addiu $t1,$zero,0x17\n"
    ".size func_8005CED8, .-func_8005CED8\n"
    ".set reorder\n"
);

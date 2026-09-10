#include "psx_types.h"

/* BIOS vector boundary called by 800429DC for indices zero/four/five/six.
 * Arguments and caller return address pass through unchanged. Keep the
 * selector in the delay slot and exclude the following alignment nop.
 * Native BIOS service behavior is not supplied by this source overlay. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005CF58\n"
    ".type func_8005CF58, @function\n"
    "func_8005CF58:\n"
    "addiu $t2, $zero, 0xC0\n"
    "jr    $t2\n"
    "addiu $t1, $zero, 0x0A\n"
    ".size func_8005CF58, .-func_8005CF58\n"
    ".set reorder\n"
);

#include "psx_types.h"

/* BIOS vector boundary called by 800429DC for callback index zero.
 * Preserve arguments and caller return address; the selector is installed
 * in the jump delay slot. The following retail alignment nop is not body.
 * Native BIOS service behavior is not supplied by this source overlay. */
__asm__(
    ".set noreorder\n"
    ".globl func_8005CF48\n"
    ".type func_8005CF48, @function\n"
    "func_8005CF48:\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr    $t2\n"
    "addiu $t1, $zero, 0x5B\n"
    ".size func_8005CF48, .-func_8005CF48\n"
    ".set reorder\n"
);

/* Main-exec range [8005CF48,8005CF54) from the SLUS executable.
 * SHA256(span)=00edef32236c975680bc303e138c5c4f0af7b8f4cc322f5bb4225de45f51726a.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x240A00B0)
MUSASHI_NATIVE_MIPS_WORD(0x01400008)
MUSASHI_NATIVE_MIPS_WORD(0x2409005B)
#else
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
#endif

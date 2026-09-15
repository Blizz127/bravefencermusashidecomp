/* Main-exec range [8005CF58,8005CF64) from the SLUS executable.
 * SHA256(span)=5679de6d872f74c1cf6e01a3593fcbf41172e1f626c0c21341d455839067f641.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x240A00C0)
MUSASHI_NATIVE_MIPS_WORD(0x01400008)
MUSASHI_NATIVE_MIPS_WORD(0x2409000A)
#else
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
#endif

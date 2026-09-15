/* Main-exec range [8005CE50,8005CE5C) from the SLUS executable.
 * SHA256(span)=d3eefd259eb1b5f648ec00610d2defbf4c6e5873f47895dd3d23a322bb0cfd7f.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x240A00A0)
MUSASHI_NATIVE_MIPS_WORD(0x01400008)
MUSASHI_NATIVE_MIPS_WORD(0x24090072)
#else
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
#endif

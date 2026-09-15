/* Main-exec range [8005CED8,8005CEE4) from the SLUS executable.
 * SHA256(span)=6403f02e44574f9166b7e8b8d3cb89a7a05b124c57f6427b05647750b30f0d1f.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x240A00B0)
MUSASHI_NATIVE_MIPS_WORD(0x01400008)
MUSASHI_NATIVE_MIPS_WORD(0x24090017)
#else
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
#endif

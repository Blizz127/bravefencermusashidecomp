/* Main-exec range [800595DC,800595EC) from the SLUS executable.
 * SHA256(span)=90d6a9f4b7055f2a0d4ddab177a7a3981937df7f27ef103ce2880b72a5ca71f4.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x90422788)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern u8 D_80072788;

/* Adjacent leaf helper recovered from retail; 4/4 words match. */
u8 func_800595DC(void) {
    return D_80072788;
}
#endif

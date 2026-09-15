/* Main-exec range [80043034,80043060) from the SLUS executable.
 * SHA256(span)=10a6fc24d646f22be8f184959bea92a50dba690615f6db08e6e1513d70c47e79.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0x10A00006)
MUSASHI_NATIVE_MIPS_WORD(0x24A2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x2403FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xAC800000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x1443FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x24840004)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Byte-exact word clear used by DMA callback initialization. */
#include "psx_types.h"
void func_80043034(u32 *destination, u32 word_count) {
    while (word_count--)
        *destination++ = 0;
}
#endif

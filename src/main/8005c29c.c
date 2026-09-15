/* Main-exec range [8005C29C,8005C2C8) from the SLUS executable.
 * SHA256(span)=bc4c08f514cc2afda0a05a2a41045b0d2c220a0f419f99d69759e72118c6450b.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0x10C00006)
MUSASHI_NATIVE_MIPS_WORD(0x24C2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x2403FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xA0850000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x1443FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Byte-exact graphics reset helper [8005C29C,8005C2C8). Byte storage and
 * unsigned countdown also permit this same body to run on bounded native RAM. */
void func_8005C29C(u8 *destination, s32 value, u32 count) {
    while (count--)
        *destination++ = value;
}
#endif

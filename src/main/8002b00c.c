/* Main-exec range [8002B00C,8002B064) from the SLUS executable.
 * SHA256(span)=47b79207fa143970ad1c4bb981b42ea9254b96db48e73f29ba122cd9d3f6da84.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00803821)
MUSASHI_NATIVE_MIPS_WORD(0x3C068007)
MUSASHI_NATIVE_MIPS_WORD(0x24C65CC0)
MUSASHI_NATIVE_MIPS_WORD(0x24C802D0)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC30004)
MUSASHI_NATIVE_MIPS_WORD(0x8CC40008)
MUSASHI_NATIVE_MIPS_WORD(0x8CC5000C)
MUSASHI_NATIVE_MIPS_WORD(0xACE20000)
MUSASHI_NATIVE_MIPS_WORD(0xACE30004)
MUSASHI_NATIVE_MIPS_WORD(0xACE40008)
MUSASHI_NATIVE_MIPS_WORD(0xACE5000C)
MUSASHI_NATIVE_MIPS_WORD(0x24C60010)
MUSASHI_NATIVE_MIPS_WORD(0x14C8FFF6)
MUSASHI_NATIVE_MIPS_WORD(0x24E70010)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC30004)
MUSASHI_NATIVE_MIPS_WORD(0x8CC40008)
MUSASHI_NATIVE_MIPS_WORD(0xACE20000)
MUSASHI_NATIVE_MIPS_WORD(0xACE30004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACE40008)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u32 w[183]; } T_8002B00C;
extern T_8002B00C D_80075CC0;
void func_8002B00C(T_8002B00C *dst) { *dst = D_80075CC0; }
#endif

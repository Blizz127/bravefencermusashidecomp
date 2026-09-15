/* Main-exec range [80043060,80043078) from the SLUS executable.
 * SHA256(span)=11d327edbd4d62f21e0b6f7e2d12a834d424337883732011b7fedece44fc0237.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42CBE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC24CBE8)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#ifdef MUSASHI_NATIVE_MEMORY_BINDING
/* Scalar boundary only: this function has no calls and touches one RAM word.
 * The port marshals that word without casting byte storage to an s32 lvalue.
 * Keep the actual exchange body shared with the retail compilation. */
#define D_8006CBE8 (*native_word)
s32 func_80043060_native(s32 arg0, s32 *native_word)
#else
extern s32 D_8006CBE8;
s32 func_80043060(s32 arg0)
#endif
{
    s32 temp_v0;

    temp_v0 = D_8006CBE8;
    D_8006CBE8 = arg0;
    return temp_v0;
}
#endif

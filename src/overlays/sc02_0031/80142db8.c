/* SC02.CD FILE_031 / ov_SC02_031 retail span [80142DB8,80142DC4).
 * Offset 0x1AC60 at overlay base 80128158. SHA256(span)=e051f2699e0264c692045685ea738e3fe652b03879a76754e46ac8010d6c19a5.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80142db8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x9482005C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x30420001)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x5C]; u16 flags; } T;
u16 func_80142DB8(T *p) { return p->flags & 1; }
#endif

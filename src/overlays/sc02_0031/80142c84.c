/* SC02.CD FILE_031 / ov_SC02_031 retail span [80142C84,80142C9C).
 * Offset 0x1AB2C at overlay base 80128158. SHA256(span)=d5aa617a084a45633699e7fd853b8e1c121ea3d0470e39451f07832e49732ce1.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80142c84.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02FFF4)
MUSASHI_NATIVE_MIPS_WORD(0xAC820014)
MUSASHI_NATIVE_MIPS_WORD(0x3C020002)
MUSASHI_NATIVE_MIPS_WORD(0xAC820048)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4800102)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x14]; s32 a; u8 pad2[0x30]; s32 b; u8 pad3[0xB6]; s16 c; } T;
void func_80142C84(T *p) {
    p->a = 0xFFF40000;
    p->b = 0x20000;
    p->c = 0;
}
#endif

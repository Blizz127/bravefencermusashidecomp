/* SC02.CD FILE_031 / ov_SC02_031 retail span [80151184,801511A8).
 * Offset 0x2902C at overlay base 80128158. SHA256(span)=8604e743440cf3b24ef9418c96c4de8212667f3ff68d5918bee0a2771843a542.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80151184.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C830020)
MUSASHI_NATIVE_MIPS_WORD(0x9482003C)
MUSASHI_NATIVE_MIPS_WORD(0xA485003E)
MUSASHI_NATIVE_MIPS_WORD(0xA4860040)
MUSASHI_NATIVE_MIPS_WORD(0x94630012)
MUSASHI_NATIVE_MIPS_WORD(0x34420001)
MUSASHI_NATIVE_MIPS_WORD(0xA482003C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4830042)
#else
#include "psx_types.h"
typedef struct Inner { u8 pad[0x12]; u16 u12; } Inner;
typedef struct {
    u8 pad[0x20]; Inner *inner;
    u8 pad24[0x18]; u16 u3C, u3E, u40, u42;
} T;
void func_80151184(T *p, s32 a1, s32 a2) {
    Inner *in = p->inner;
    p->u3E = a1;
    p->u40 = a2;
    p->u42 = in->u12;
    p->u3C |= 1;
}
#endif

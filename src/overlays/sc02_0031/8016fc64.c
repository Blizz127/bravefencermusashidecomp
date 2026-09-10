/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016FC64,8016FC90).
 * Offset 0x47B0C at overlay base 80128158. SHA256(span)=6aec008a3fc150f262fb3bad533f598f70b76baeba78bb51e0292eeef9d78ac3.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016fc64.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x8C830020)
MUSASHI_NATIVE_MIPS_WORD(0x94820132)
MUSASHI_NATIVE_MIPS_WORD(0xA4800136)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C64A)
MUSASHI_NATIVE_MIPS_WORD(0xA4620012)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
void func_80171928();
typedef struct Inner { u8 pad[0x12]; u16 unk12; } Inner;
typedef struct {
    u8 pad[0x20];
    Inner *inner;
    u8 pad24[0x132-0x24];
    u16 f132;
    u8 pad134[2];
    s16 f136;
} T;
void func_8016FC64(T *p) {
    p->f136 = 0;
    p->inner->unk12 = p->f132;
    func_80171928(p);
}
#endif

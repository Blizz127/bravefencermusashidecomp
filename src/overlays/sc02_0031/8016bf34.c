/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016BF34,8016BF50).
 * Offset 0x43DDC at overlay base 80128158. SHA256(span)=8e3cfeb5f6d2a8d5494bdcce39a680ce6247d390983ba368b88e7e04bd7b613f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016bf34.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x94820006)
MUSASHI_NATIVE_MIPS_WORD(0x9483000A)
MUSASHI_NATIVE_MIPS_WORD(0x9485000E)
MUSASHI_NATIVE_MIPS_WORD(0xA4820012)
MUSASHI_NATIVE_MIPS_WORD(0xA4830016)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA485001A)
#else
#include "psx_types.h"
typedef struct { u8 pad[6]; u16 a; u8 pad8[2]; u16 b; u8 padC[2]; u16 c;
    u8 pad10[2]; u16 d; u8 pad14[2]; u16 e; u8 pad18[2]; u16 f; } T;
void func_8016BF34(T *p) {
    p->d = p->a;
    p->e = p->b;
    p->f = p->c;
}
#endif

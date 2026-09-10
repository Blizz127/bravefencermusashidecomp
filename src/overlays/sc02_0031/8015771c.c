/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015771C,8015773C).
 * Offset 0x2F5C4 at overlay base 80128158. SHA256(span)=8d2d7fba10193f2840a200c82164b521dafe6c9ae893648aedb45697fac29966.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015771c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C055DCF)
MUSASHI_NATIVE_MIPS_WORD(0xA08001AA)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
void func_8015773C();
typedef struct { u8 pad[0x1AA]; u8 f; } T;
void func_8015771C(T *p) {
    p->f = 0;
    func_8015773C(p);
}
#endif

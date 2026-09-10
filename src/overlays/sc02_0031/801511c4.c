/* SC02.CD FILE_031 / ov_SC02_031 retail span [801511C4,801511E0).
 * Offset 0x2906C at overlay base 80128158. SHA256(span)=f6e6864f3814bfa3c378ae754fca99c11d3374b7aff9a2781ddd2f88bdc962f8.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801511c4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x9482003E)
MUSASHI_NATIVE_MIPS_WORD(0x94830040)
MUSASHI_NATIVE_MIPS_WORD(0x94850042)
MUSASHI_NATIVE_MIPS_WORD(0xA48200F0)
MUSASHI_NATIVE_MIPS_WORD(0xA48300F2)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA48500F4)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x3E]; u16 a, b, c; u8 pad44[0xAC]; u16 d, e, f; } T;
void func_801511C4(T *p) {
    p->d = p->a;
    p->e = p->b;
    p->f = p->c;
}
#endif

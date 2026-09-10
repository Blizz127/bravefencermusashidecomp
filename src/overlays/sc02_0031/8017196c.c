/* SC02.CD FILE_031 / ov_SC02_031 retail span [8017196C,8017197C).
 * Offset 0x49814 at overlay base 80128158. SHA256(span)=f14873a548f1d155ea74e84cbe7bb0b2c309d3c4d520f8bd693da8221358df36.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8017196c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xA0850214)
MUSASHI_NATIVE_MIPS_WORD(0xA0800215)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0800216)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x214]; u8 u214, u215, u216; } T;
void func_8017196C(T *p, s32 a1) {
    p->u214 = a1;
    p->u215 = 0;
    p->u216 = 0;
}
#endif

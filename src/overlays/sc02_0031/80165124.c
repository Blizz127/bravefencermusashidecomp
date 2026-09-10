/* SC02.CD FILE_031 / ov_SC02_031 retail span [80165124,80165140).
 * Offset 0x3CFCC at overlay base 80128158. SHA256(span)=d915d84ad6be018187ddd859660cec4f179fc8a12560265e8c5c07c04b5facc6.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80165124.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x94820062)
MUSASHI_NATIVE_MIPS_WORD(0x94830062)
MUSASHI_NATIVE_MIPS_WORD(0x94850062)
MUSASHI_NATIVE_MIPS_WORD(0xA0820050)
MUSASHI_NATIVE_MIPS_WORD(0xA0830051)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0850052)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x50]; u8 a, b, c; u8 pad53[0xF]; u16 u62; } T;
void func_80165124(T *p) {
    p->a = p->u62;
    p->b = p->u62;
    p->c = p->u62;
}
#endif

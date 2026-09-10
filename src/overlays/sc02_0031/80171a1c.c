/* SC02.CD FILE_031 / ov_SC02_031 retail span [80171A1C,80171A34).
 * Offset 0x498C4 at overlay base 80128158. SHA256(span)=cbcdc56256facabaaa414ecec4e6262b153ac9c767b43af3bd5f9131217a48ad.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80171a1c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x90820214)
MUSASHI_NATIVE_MIPS_WORD(0xA0800215)
MUSASHI_NATIVE_MIPS_WORD(0xA0800216)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0820214)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x214]; u8 a, b, c; } T;
void func_80171A1C(T *p) {
    p->b = 0;
    p->c = 0;
    p->a++;
}
#endif

/* SC02.CD FILE_031 / ov_SC02_031 retail span [8014A680,8014A69C).
 * Offset 0x22528 at overlay base 80128158. SHA256(span)=132d056f3e7b8a198df2da2b34557521df4510f81902478e8d864f073a7feb23.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8014a680.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x908201BC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xA08201BC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x1BC]; u8 v; } T;
void func_8014A680(T *p) {
    if (p->v) {
        p->v = p->v - 1;
    }
}
#endif

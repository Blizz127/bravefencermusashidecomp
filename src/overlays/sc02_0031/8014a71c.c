/* SC02.CD FILE_031 / ov_SC02_031 retail span [8014A71C,8014A738).
 * Offset 0x225C4 at overlay base 80128158. SHA256(span)=d5b42a4625dd7dd40034e2c90ef522a214734eb1e427633920bf1affe27d89b3.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8014a71c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x908201BE)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xA08201BE)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x1BE]; u8 v; } T;
void func_8014A71C(T *p) {
    if (p->v) {
        p->v = p->v - 1;
    }
}
#endif

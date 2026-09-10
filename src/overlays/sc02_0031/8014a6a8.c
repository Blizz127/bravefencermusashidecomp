/* SC02.CD FILE_031 / ov_SC02_031 retail span [8014A6A8,8014A6C4).
 * Offset 0x22550 at overlay base 80128158. SHA256(span)=bba4ffc45dabaf0afbaf98416c5d88b05d750f857a78158dff1dd8ae68ab3404.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8014a6a8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x908201BD)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xA08201BD)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x1BD]; u8 v; } T;
void func_8014A6A8(T *p) {
    if (p->v) {
        p->v = p->v - 1;
    }
}
#endif

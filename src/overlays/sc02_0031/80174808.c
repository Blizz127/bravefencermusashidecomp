/* SC02.CD FILE_031 / ov_SC02_031 retail span [80174808,8017481C).
 * Offset 0x4C6B0 at overlay base 80128158. SHA256(span)=52cd556ded98e83c61cf753d2a2480e1e5c41cc57aa94e589a8e8a1ac62a8519.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80174808.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x90820214)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0820214)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x214]; u8 u214; } T;
void func_80174808(T *p) {
    p->u214 = p->u214 + 1;
}
#endif

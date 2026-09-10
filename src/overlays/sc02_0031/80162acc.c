/* SC02.CD FILE_031 / ov_SC02_031 retail span [80162ACC,80162AE0).
 * Offset 0x3A974 at overlay base 80128158. SHA256(span)=7f8d0c89fdfba35e91bfa5dd9a24914f5248f6eae2b023b189a7cdc54ad10e0b.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80162acc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x90820001)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0820001)
#else
#include "psx_types.h"
typedef struct { u8 pad; u8 u1; } T;
void func_80162ACC(T *p) {
    p->u1 = p->u1 + 1;
}
#endif

/* SC02.CD FILE_031 / ov_SC02_031 retail span [801553A8,801553C0).
 * Offset 0x2D250 at overlay base 80128158. SHA256(span)=3d2cab15a2c361f1e329a01ed12bcb9fea650730daf46667490be0521cf411f1.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801553a8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C03DFFF)
MUSASHI_NATIVE_MIPS_WORD(0x8C820044)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820044)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x44]; s32 flags; } T;
void func_801553A8(T *p) {
    p->flags &= ~0x20000000;
}
#endif

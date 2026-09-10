/* SC02.CD FILE_031 / ov_SC02_031 retail span [80154BC8,80154BE4).
 * Offset 0x2CA70 at overlay base 80128158. SHA256(span)=37985f3d5f2058feebf1d4cf6e60309143174eaff6e8c680f63495eb4abd5c84.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80154bc8.c (m2c-derived, oracle MATCH); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xAC8500D0)
MUSASHI_NATIVE_MIPS_WORD(0xA48200D6)
MUSASHI_NATIVE_MIPS_WORD(0xA48200D4)
MUSASHI_NATIVE_MIPS_WORD(0xA08600D8)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA08600D9)
#else
#include "psx_types.h"
typedef struct { u8 pad[0xD0]; s32 d0; s16 d4, d6; u8 d8, d9; } T;
void func_80154BC8(T *p, s32 a1, u8 a2) {
    p->d0 = a1;
    p->d6 = 1;
    p->d4 = 1;
    p->d8 = a2;
    p->d9 = a2;
}
#endif

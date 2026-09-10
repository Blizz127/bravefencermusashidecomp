/* SC02.CD FILE_031 / ov_SC02_031 retail span [80154B20,80154B4C).
 * Offset 0x2C9C8 at overlay base 80128158. SHA256(span)=4e040fb9eb15596366695882ca60e677577a039e39c73520d2840416819f147f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80154b20.c (m2c-derived, oracle MATCH); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C8200CC)
MUSASHI_NATIVE_MIPS_WORD(0x00052880)
MUSASHI_NATIVE_MIPS_WORD(0x00A22821)
MUSASHI_NATIVE_MIPS_WORD(0x8CA30000)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xA48200D6)
MUSASHI_NATIVE_MIPS_WORD(0xA48200D4)
MUSASHI_NATIVE_MIPS_WORD(0xA08600D8)
MUSASHI_NATIVE_MIPS_WORD(0xA08600D9)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC8300D0)
#else
#include "psx_types.h"
typedef struct {
    u8 pad[0xCC]; s32 *cc; s32 d0; s16 d4, d6; u8 d8, d9;
} T;
void func_80154B20(T *p, s32 a1, u8 a2) {
    s32 v = p->cc[a1];
    p->d6 = 1;
    p->d4 = 1;
    p->d8 = a2;
    p->d9 = a2;
    p->d0 = v;
}
#endif

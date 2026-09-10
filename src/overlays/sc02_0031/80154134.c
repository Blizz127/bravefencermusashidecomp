/* SC02.CD FILE_031 / ov_SC02_031 retail span [80154134,80154150).
 * Offset 0x2BFDC at overlay base 80128158. SHA256(span)=df844632cbc605c52a1b9346b11c83679a4f229370b222b6203c7bcfbc485028.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80154134.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xAC8000B4)
MUSASHI_NATIVE_MIPS_WORD(0xA48000BA)
MUSASHI_NATIVE_MIPS_WORD(0xA48000B8)
MUSASHI_NATIVE_MIPS_WORD(0xA08000BD)
MUSASHI_NATIVE_MIPS_WORD(0xA08000BC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA08000DC)
#else
#include "psx_types.h"
typedef struct {
    u8 pad[0xB4]; s32 b4; s16 b8, ba; u8 bc, bd;
    u8 padBE[0x1E]; u8 dc;
} T;
void func_80154134(T *p) {
    p->b4 = 0;
    p->ba = 0;
    p->b8 = 0;
    p->bd = 0;
    p->bc = 0;
    p->dc = 0;
}
#endif

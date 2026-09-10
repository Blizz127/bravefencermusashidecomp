/* SC02.CD FILE_031 / ov_SC02_031 retail span [80172560,80172588).
 * Offset 0x4A408 at overlay base 80128158. SHA256(span)=137089fa4af940f85e0d92cb4dc29b9c4cb0ef35d864548877fb3614087a5813.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80172560.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x9482000A)
MUSASHI_NATIVE_MIPS_WORD(0x24840004)
MUSASHI_NATIVE_MIPS_WORD(0x0C004D14)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20002)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x28420010)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
#else
#include "psx_types.h"
s32 func_80013450();
typedef struct { u8 pad[0xA]; u16 unkA; } T;
typedef struct { u8 pad[2]; s16 unk2; } U;
s32 func_80172560(T *p, U *q) {
    q->unk2 = p->unkA;
    return func_80013450((u8 *)p + 4) < 0x10;
}
#endif

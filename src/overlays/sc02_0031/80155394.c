/* SC02.CD FILE_031 / ov_SC02_031 retail span [80155394,801553A8).
 * Offset 0x2D23C at overlay base 80128158. SHA256(span)=08e91219effc194c5f807bc8eb65638d35e9f75820c3c739f32c57404c5b2c24.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80155394.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C820044)
MUSASHI_NATIVE_MIPS_WORD(0x3C032000)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820044)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x44]; s32 flags; } T;
void func_80155394(T *p) {
    p->flags |= 0x20000000;
}
#endif

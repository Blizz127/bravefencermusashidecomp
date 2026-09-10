/* SC02.CD FILE_031 / ov_SC02_031 retail span [801748C4,801748E4).
 * Offset 0x4C76C at overlay base 80128158. SHA256(span)=e399530aba71398684d70d1795702e700d0029c53799d27f53298e382dd8b79b.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801748c4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C030400)
MUSASHI_NATIVE_MIPS_WORD(0x90850214)
MUSASHI_NATIVE_MIPS_WORD(0x8C820044)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0xAC820044)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0850214)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x44]; s32 flags; u8 pad48[0x214-0x48]; u8 unk214; } T;
void func_801748C4(T *p) {
    p->flags |= 0x4000000;
    p->unk214++;
}
#endif

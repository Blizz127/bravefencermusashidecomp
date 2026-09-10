/* SC02.CD FILE_031 / ov_SC02_031 retail span [80132EC4,80132EF4).
 * Offset 0xAD6C at overlay base 80128158. SHA256(span)=1f9f0f3b09308b2a6ed44ce2ee642ce1aaa1b3ad237f0b2e325c99df7cab7edc.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80132ec4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4850004)
MUSASHI_NATIVE_MIPS_WORD(0x24840008)
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_80132EC4 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): frameless 2-arg void.
 * If arg0[0] == 0, returns at once; else do { arg0+4 = (u16)arg1;
 * arg0 += 8; } while (arg0[0] != 0). The sh truncates arg1 to its
 * low halfword; stride-8 nodes modelled as {s32, u16, pad}. */

struct node_80132EC4 {
    s32 unk0;
    u16 unk4;
    u8 pad[0x2];
};

void func_80132EC4(struct node_80132EC4 *arg0, s32 arg1) {
    if (arg0->unk0 == 0) {
        return;
    }
    do {
        arg0->unk4 = arg1;
        arg0++;
    } while (arg0->unk0 != 0);
}
#endif

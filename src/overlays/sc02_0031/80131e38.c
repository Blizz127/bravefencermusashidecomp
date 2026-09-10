/* SC02.CD FILE_031 / ov_SC02_031 retail span [80131E38,80131E7C).
 * Offset 0x9CE0 at overlay base 80128158. SHA256(span)=80cd80415dd09828ea1768a97304b5c1f79eefbea00cf93ef1b3c69337404efe.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80131e38.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x2402000F)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0xA08200C1)
MUSASHI_NATIVE_MIPS_WORD(0x8C8200B4)
MUSASHI_NATIVE_MIPS_WORD(0x3C030004)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x24020006)
MUSASHI_NATIVE_MIPS_WORD(0xAC82001C)
MUSASHI_NATIVE_MIPS_WORD(0xA480005C)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x24050039)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_80131E38 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): s32 result, 0x18
 * frame. Flags byte 0xC1 = 0xF; if (word 0xB4 & 0x40000):
 * word 0x1C = 6, half 0x5C = 0. Tail-calls func_80131CA8(arg0,
 * 0x39) with a0 still live (no a-reg writes precede the jal) and
 * returns its result. Caller-side void* decl per the
 * func_80131D68 precedent. */

struct st_80131E38 {
    u8 pad[0x1C];
    s32 w1C;
    u8 pad20[0x3C];
    u16 h5C;
    u8 pad5E[0x56];
    s32 wB4;
    u8 padB8[0x9];
    u8 bC1;
};

extern s32 func_80131CA8(void *arg0, s32 arg1);

s32 func_80131E38(struct st_80131E38 *arg0) {
    arg0->bC1 = 0xF;
    if ((arg0->wB4 & 0x40000) != 0) {
        arg0->w1C = 6;
        arg0->h5C = 0;
    }
    return func_80131CA8(arg0, 0x39);
}
#endif

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

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

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801376C8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void*-forwarding
 * adapter, 0x18 frame. Returns func_801376E8(a0-live, 0) (a0
 * untouched past the ra save: passthrough; a1 = 0 in the jal
 * delay slot). */

struct hw2_801376C8 {
    u16 unk0;
    u16 unk2;
};

extern void *func_801376E8(void *arg0, struct hw2_801376C8 *arg1);

void *func_801376C8(void *arg0) {
    return func_801376E8(arg0, 0);
}

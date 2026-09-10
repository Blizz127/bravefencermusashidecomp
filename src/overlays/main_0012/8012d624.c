/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012D624 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Triple init grounded as lhu (u16); the third half is stored in the jal delay slot. a1/a2 pass through untouched to func_8012D664 (true 3-parameter signature; m2c missed the forwarding), and the call result is returned (v0 untouched to jr). */

extern s32 func_8012D664(void *arg0, s32 arg1, void *arg2);

s32 func_8012D624(void *arg0, s32 arg1, void *arg2) {
    u16 h[3];

    h[0] = ((u16 *) arg0)[3];
    h[1] = ((u16 *) arg0)[5];
    h[2] = ((u16 *) arg0)[7];
    return func_8012D664(h, arg1, arg2);
}


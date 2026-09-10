/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80128C98 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): v = lh
 * D_8017E630[arg0] (s16 table, sll-1 index); when negative
 * returns 1, else returns func_8001ABBC(0, 0, &D_800AE830 +
 * (v << 3), D_80182D1C, 0) (shift/add in bltz delay + addu;
 * zero stack slot in jal delay). */

extern s16 D_8017E630[];
extern u8 D_800AE830;
extern s32 func_8001ABBC(s32 arg0, s32 arg1, void *arg2, s32 arg3, void *arg4);
extern s32 D_80182D1C;

s32 func_80128C98(s32 arg0) {
    s16 v;

    v = D_8017E630[arg0];
    if (v < 0) {
        return 1;
    }
    return func_8001ABBC(0, 0, &D_800AE830 + (v << 3), D_80182D1C, 0);
}

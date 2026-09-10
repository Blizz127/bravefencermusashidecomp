/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012BF7C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Halves grounded as lh (s16); bgez skip-negation then slti 0x360 matches the abs/compare shape (inversion after slti). */

extern s16 D_80126CB0;

struct pt_8012BF7C {
    u8 pad[0xE];
    s16 unkE;
};

s32 func_8012BF7C(struct pt_8012BF7C *arg0) {
    s32 var_v0;

    var_v0 = arg0->unkE - D_80126CB0;
    if (var_v0 < 0) {
        var_v0 = -var_v0;
    }
    return var_v0 >= 0x360;
}


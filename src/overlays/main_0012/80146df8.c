/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80146DF8 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Symmetric triple clamp (each of arg1/arg2/arg3
 * clamped against -arg4/arg4) stored as words at +0x24/+0x28/+0x2C
 * (sw). The clamped values stay in argument registers ($a1-$a3) at
 * the stores, which this direct transcription preserves. Body is
 * m2c's verbatim with types filled in. */

struct data_80146DF8 {
    u8 pad[0x24];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
};

void func_80146DF8(struct data_80146DF8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;

    var_a1 = arg1;
    var_a2 = arg2;
    var_a3 = arg3;
    if (var_a1 < 0) {
        temp_v1 = -arg4;
        if (var_a1 < temp_v1) {
            var_a1 = temp_v1;
        }
    } else if (arg4 < var_a1) {
        var_a1 = arg4;
    }
    if (var_a2 < 0) {
        temp_v1_2 = -arg4;
        if (var_a2 < temp_v1_2) {
            var_a2 = temp_v1_2;
        }
    } else if (arg4 < var_a2) {
        var_a2 = arg4;
    }
    if (var_a3 < 0) {
        temp_v1_3 = -arg4;
        if (var_a3 < temp_v1_3) {
            var_a3 = temp_v1_3;
        }
    } else if (arg4 < var_a3) {
        var_a3 = arg4;
    }
    arg0->unk24 = var_a1;
    arg0->unk28 = var_a2;
    arg0->unk2C = var_a3;
}

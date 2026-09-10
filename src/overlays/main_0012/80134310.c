/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80134310 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): frameless 3-arg s32
 * leaf. Returns arg0[0]*arg1[0] + arg0[1]*arg1[1] + arg0[2]*arg1[2]
 * + arg2 (three mult/mflo lows summed with the bias in the jr
 * delay slot): a signed-halfword 3-dot-product plus bias. s16
 * products are exact; the final sum wraps mod 2^32 exactly as the
 * addu chain. */

s32 func_80134310(s16 *arg0, s16 *arg1, s32 arg2) {
    return arg0[0] * arg1[0] + arg0[1] * arg1[1] + arg0[2] * arg1[2] + arg2;
}

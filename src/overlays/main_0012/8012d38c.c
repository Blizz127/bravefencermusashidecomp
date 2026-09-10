/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012D38C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Raw shows a0 untouched (only a1 = 0 in the jal delay slot), so the object pointer passes through: true signature takes it. (Trailing double jr is dead padding.) */

void func_8012D098(void *arg0, s32 arg1);

void func_8012D38C(void *arg0) {
    func_8012D098(arg0, 0);
}


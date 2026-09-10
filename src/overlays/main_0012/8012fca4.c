/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012FCA4 (main_0012.s), decoded manually from
 * raw asm (0x20 bytes; m2c 1-arg misread corrected: a0 is never
 * written, so the incoming a0 passes through to the call;
 * NOT verified against retail; C89-gated only, promotion
 * requires an oracle MATCH): calls 31CA8(arg0, 0x1B). */

extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012FCA4(void *arg0) {
    func_80131CA8(arg0, 0x1B);
}

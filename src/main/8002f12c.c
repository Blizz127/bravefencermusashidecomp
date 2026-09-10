/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8002F12C (main.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Word value at +0x4 (lw) passed on. Body is m2c's verbatim with the
 * member typed. */

struct data_8002F12C {
    u8 pad[0x4];
    s32 unk4; };

void func_8002DC68(s32, s32);

void func_8002F12C(struct data_8002F12C *arg0) {
    func_8002DC68(arg0->unk4, 0);
}

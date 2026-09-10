/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80149350 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Word value at +0x20 (lw) plus 0x34 passed on. Body is m2c's verbatim with the
 * member typed. */

struct data_80149350 {
    u8 pad[0x20];
    s32 unk20; };

void func_8012F14C(s32);

void func_80149350(struct data_80149350 *arg0) {
    func_8012F14C(arg0->unk20 + 0x34);
}

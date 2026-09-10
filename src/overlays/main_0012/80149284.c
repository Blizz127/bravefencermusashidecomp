/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80149284 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Word test at +0x1DC (lw). Body is m2c's verbatim with the
 * member typed. */

struct data_80149284 {
    u8 pad[0x1DC];
    s32 unk1DC; };

s32 func_80149284(struct data_80149284 *arg0, s32 arg1) {
    return arg0->unk1DC & arg1;
}

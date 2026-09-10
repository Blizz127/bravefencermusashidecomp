/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80146E90 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Word store of the argument (sw). Body is m2c's verbatim with the
 * member typed. */

struct data_80146E90 {
    u8 pad[0x1C];
    s32 unk1C; };

void func_80146E90(struct data_80146E90 *arg0, s32 arg1) {
    arg0->unk1C = arg1;
}

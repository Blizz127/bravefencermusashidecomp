/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_801490F0 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Halfword store of the s16 argument (sh). Body is m2c's verbatim with the
 * member typed. */

struct data_801490F0 {
    u8 pad[0x10C];
    s16 unk10C; };

void func_801490F0(struct data_801490F0 *arg0, s16 arg1) {
    arg0->unk10C = arg1;
}

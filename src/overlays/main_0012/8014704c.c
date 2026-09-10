/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8014704C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Byte zero-store (sb). Body is m2c's verbatim with the
 * member typed. */

struct data_8014704C {
    u8 pad[0x4C];
    u8 unk4C; };

void func_8014704C(struct data_8014704C *arg0) {
    arg0->unk4C = 0;
}

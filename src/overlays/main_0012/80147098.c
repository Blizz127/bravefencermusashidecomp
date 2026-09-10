/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80147098 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Byte zero-store (sb). Body is m2c's verbatim with the
 * member typed. */

struct data_80147098 {
    u8 pad[0x220];
    u8 unk220; };

void func_80147098(struct data_80147098 *arg0) {
    arg0->unk220 = 0;
}

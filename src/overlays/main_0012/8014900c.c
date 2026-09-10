/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8014900C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Halfword RMW setting bit 15 at +0x3C (sh; the
 * draft's (u16) cast is right). Body is m2c's verbatim with the
 * member typed. */

struct data_8014900C {
    u8 pad[0x3C];
    u16 unk3C;
};

void func_8014900C(struct data_8014900C *arg0) {
    arg0->unk3C = (u16) (arg0->unk3C | 0x8000);
}

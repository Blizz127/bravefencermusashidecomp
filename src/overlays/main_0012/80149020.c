/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80149020 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Halfword RMW clearing bit 15 (lhu/sh). Body is m2c's verbatim with the
 * member typed. */

struct data_80149020 {
    u8 pad[0x3C];
    u16 unk3C; };

void func_80149020(struct data_80149020 *arg0) {
    arg0->unk3C = (u16) (arg0->unk3C & 0x7FFF);
}

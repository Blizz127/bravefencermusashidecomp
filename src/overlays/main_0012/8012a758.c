/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012A758 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Call chain grounded from raw asm: A7D4(sp+0x10, sp+0x18) then A79C with the same pair. */

struct pair_8012A7D4 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

void func_8012A7D4(struct pair_8012A7D4 *arg0, struct pair_8012A7D4 *arg1);
s16 func_8012A79C(struct pair_8012A7D4 *arg0, struct pair_8012A7D4 *arg1);

s16 func_8012A758(void) {
    struct pair_8012A7D4 sp10;
    struct pair_8012A7D4 sp18;

    func_8012A7D4(&sp10, &sp18);
    return func_8012A79C(&sp10, &sp18);
}


/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012A908 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Loop shape from m2c; widths grounded from raw asm (lh D_801270C0, lh+andi 0x1000 on unk72, +0x10C step, 0x60 iterations). */

struct entry_8012A908 {
    u8 pad[0x72];
    u16 unk72;
    u8 pad2[0x98];
};

extern struct entry_8012A908 D_801202A0[0x60];
extern s16 D_801270C0;

void func_8012A988(struct entry_8012A908 *arg0);

void func_8012A908(void) {
    struct entry_8012A908 *var_s0;
    s32 var_s1;

    var_s0 = D_801202A0;
    var_s1 = 0;
    do {
        if ((D_801270C0 == 1) || (var_s0->unk72 & 0x1000)) {
            func_8012A988(var_s0);
        }
        var_s1 += 1;
        var_s0 += 1;
    } while (var_s1 < 0x60);
}


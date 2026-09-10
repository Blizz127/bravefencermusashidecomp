/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012AD44 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Store widths grounded from raw asm (sh at 0x2 and 0x34). */

struct obj_8012AD44 {
    s16 unk0;
    s16 unk2;
    u8 pad[0x30];
    s16 unk34;
};

void func_8012AD44(struct obj_8012AD44 *arg0, s16 arg1) {
    arg0->unk2 = arg1;
    arg0->unk34 = 0;
}


/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012AD6C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Read-modify-write at 0x34 grounded from raw asm (addiu 1, sh). */

struct obj_8012AD64 {
    u8 pad[0x34];
    s16 unk34;
};

void func_8012AD6C(struct obj_8012AD64 *arg0) {
    arg0->unk34 = arg0->unk34 + 1;
}


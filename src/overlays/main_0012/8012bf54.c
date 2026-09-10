/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012BF54 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. lhu/sh pair grounded from raw asm (u16 bit set). */

struct obj_8012BF54 {
    u8 pad[0x5C];
    u16 unk5C;
};

void func_8012BF54(struct obj_8012BF54 *arg0) {
    arg0->unk5C |= 0x8000;
}


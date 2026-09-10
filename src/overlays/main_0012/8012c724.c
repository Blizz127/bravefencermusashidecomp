/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012C724 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. func_8012C890 is declared here as an s32 value-flow view (opaque word in, opaque word out); the true (src, dst, ctx) prototype lives in staging/hand/func_8012C890.c. Takes two arguments (m2c missed the second): the destination pointer passes through untouched in a1 while a2 is explicitly zeroed, so the context is NULL. */

struct src_8012C724 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    s32 unk10;
};

extern s32 func_8012C890(void *arg0, void *arg1, void *arg2);

void func_8012C724(struct src_8012C724 *arg0, void *arg1) {
    arg0->unkA |= 0x8000;
    func_8012C890(arg0, arg1, 0);
}


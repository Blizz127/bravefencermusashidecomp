/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_801730FC (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shape: arg0->unkB8 & 0x8000 on a void*. The disassembly loads
 * it as a halfword (lhu +0xB8), so the model declares one u16 at
 * +0xB8 — same flags member as the other 0xB8-family functions. The
 * global is an s16 per the draft (kept; the branch only tests
 * nonzero). func_80147060 was missing from the draft's declarations
 * and is added per the repo pipeline convention. Body is m2c's
 * verbatim. */

struct data_801730FC {
    u8 pad[0xB8];
    u16 unkB8;
};

void func_80154150(void *, s32);
void func_80171A1C();
void func_80174650(void *);
extern s16 D_80126B30;
void func_80147060();

void func_801730FC(struct data_801730FC *arg0) {
    if (arg0->unkB8 & 0x8000) {
        func_80171A1C();
        if (D_80126B30 != 0) {
            func_80147060(arg0);
            func_80154150(arg0, 0);
        }
        func_80174650(arg0);
    }
}

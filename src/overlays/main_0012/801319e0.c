/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801319E0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): incoming a1 is dead
 * (overwritten by the first jal delay slot). If
 * func_80131CA8(s0, 0x11) == 0: when word s0->unk78 != 0,
 * func_8002A04C(s0); then func_8012C218(s0). Returns void. */

struct obj_801319E0 {
    u8 pad[0x78];
    u32 unk78;
};

extern s32 func_80131CA8(void *arg0, s32 arg1);
extern void func_8002A04C(void *arg0);
extern void func_8012C218(void *arg0);

void func_801319E0(struct obj_801319E0 *arg0) {
    if (func_80131CA8(arg0, 0x11) == 0) {
        if (arg0->unk78 != 0) {
            func_8002A04C(arg0);
        }
        func_8012C218(arg0);
    }
}

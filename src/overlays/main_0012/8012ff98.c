/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012FF98 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Flag word at +0xB4 (lw, & 0x20), pointer at +0x20
 * (lw, null-tested) with a word RMW at +0x4 through it (lw/sw,
 * ^ 0x80000000). The model declares s32, pointer, s32. NULL is
 * spelled 0. The ?-prototypes follow the repo pipeline convention
 * (s32 return where compared, void with word-sized params
 * otherwise). Body is m2c's verbatim. */

struct inner_8012FF98 {
    u8 pad[4];
    s32 unk4;
};

struct data_8012FF98 {
    u8 pad[0x20];
    struct inner_8012FF98 *unk20;
    u8 pad2[0x90];
    s32 unkB4;
};

s32 func_8012BEE8(void *);
void func_80130D48(void *);
void func_801319E0(void *);
void func_80131CA8(void *, s32);

void func_8012FF98(struct data_8012FF98 *arg0) {
    struct inner_8012FF98 *temp_a0;

    if (arg0->unkB4 & 0x20) {
        temp_a0 = arg0->unk20;
        if (temp_a0 != 0) {
            temp_a0->unk4 = (s32) (temp_a0->unk4 ^ 0x80000000);
        }
        if (func_8012BEE8(arg0) != 0) {
            func_80130D48(arg0);
            func_801319E0(arg0);
        }
    }
    func_80131CA8(arg0, 0x10);
}

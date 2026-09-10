/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012D3B4 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Fully grounded from raw asm: alloc 0x10, sw flag from arg2 in the jal delay slot, AF648 pair, two 8004955C gates each requiring (result > 0 via blez, out-word >= 0 via bltz), then the table call with (base + first*4, obj). 80058C6C takes two arguments: like the func_8004CFEC case, the third live register at func_8012CFA8's site is leftover liveness, since this site never sets a2. */

struct obj_8012D3B4 {
    u8 pad[4];
    s32 unk4;
};

struct ride_800A651C {
    s32 base;
    u8 pad[0x10];
};

extern struct ride_800A651C D_800A651C[];
extern u16 D_800B9A02;
extern u8 D_800AF648;

extern void *func_80010A08(s32 arg0);
extern void func_80058E9C(void *arg0);
extern void func_8004914C(void *arg0);
extern void func_800491AC(void *arg0);
extern s32 func_8004955C(s32 arg0, void *arg1, void *arg2, s32 *arg3);
extern void func_80058C6C(void *arg0, void *arg1);

void func_8012D3B4(s32 arg0, s32 arg1, s32 arg2) {
    struct obj_8012D3B4 *t;
    s32 sp14;
    s32 sp10;
    s32 first;
    u16 idx;

    t = (struct obj_8012D3B4 *) func_80010A08(0x10);
    t->unk4 = arg2;
    func_80058E9C(t);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    first = func_8004955C(arg0, (u8 *) t + 8, &sp10, &sp14);
    if ((first > 0) && (sp14 >= 0)
        && (func_8004955C(arg1, (u8 *) t + 0xC, &sp10, &sp14) > 0) && (sp14 >= 0)) {
        idx = D_800B9A02;
        func_80058C6C((void *) (D_800A651C[idx].base + first * 4), t);
    }
}


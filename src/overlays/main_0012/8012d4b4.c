/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012D4B4 (main_0012.s), decoded manually from
 * raw asm (m2c left operands unknown): NOT verified against
 * retail. C89-gated only; promotion requires an oracle MATCH.
 * Same gated-table-call shape as func_8012D3B4, but the two
 * 8004955C input buffers come from func_8012F214 out-params
 * (F214#1(arg0, arg1, b1), F214#2(arg0, arg2, b2)) instead of
 * plain arguments; the second s32 parameter only forwards into
 * F214#1. Buffer sizes are unknown (only addresses escape), so
 * the stack slots are representative. 8004955C is declared with
 * a void* first parameter here (buffers) versus s32 in
 * func_8012D3B4.c (integer keys): call-site views of one
 * address-or-integer operand. Trailing double jr is dead
 * padding. */

struct obj_8012D4B4 {
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

extern void func_8012F214(void *arg0, s32 arg1, void *arg2);
extern void *func_80010A08(s32 arg0);
extern void func_80058E9C(void *arg0);
extern void func_8004914C(void *arg0);
extern void func_800491AC(void *arg0);
extern s32 func_8004955C(void *arg0, void *arg1, void *arg2, s32 *arg3);
extern void func_80058C6C(void *arg0, void *arg1);

void func_8012D4B4(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    u8 b1[8];
    u8 b2[8];
    s32 o1;
    s32 o2;
    struct obj_8012D4B4 *t;
    s32 first;
    u16 idx;

    func_8012F214(arg0, arg1, b1);
    func_8012F214(arg0, arg2, b2);
    t = (struct obj_8012D4B4 *) func_80010A08(0x10);
    t->unk4 = arg3;
    func_80058E9C(t);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    first = func_8004955C(b1, (u8 *) t + 8, &o1, &o2);
    if ((first > 0) && (o2 >= 0)
        && (func_8004955C(b2, (u8 *) t + 0xC, &o1, &o2) > 0) && (o2 >= 0)) {
        idx = D_800B9A02;
        func_80058C6C((void *) (D_800A651C[idx].base + first * 4), t);
    }
}

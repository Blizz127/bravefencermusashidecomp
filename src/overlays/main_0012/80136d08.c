/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80136D08 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (s32, s32),
 * 0x30 frame. Engine-init sequence over a 0x14-byte block from
 * func_80010A08: 4914C/491AC(&D_800AF648), s1 = malloc(0x14),
 * 58EB0(s1), two func_8004955C calls (s2, s1+8, out1, out2) and
 * (s3, s1+0x10, out1, out2) with pre-call byte pokes s1[4] =
 * 0xFF, s1[5]/[6]/[0xC]/[0xD] = 0x80, s1[0xE] = 0xFF (the s1[6]
 * store rides the first jal's delay slot), then
 * func_80058C6C(D_800A651C[v1 * 5] + (((r1 + r2) >> 3) << 2),
 * s1) where v1 = (u16)D_800B9A02 and r1/r2 are the 4955C
 * results. The 58C6C second arg is deterministically s1 (set
 * post-second-jal, untouched by the index math -- not residue),
 * matching the staged 2-arg decl; its result is ignored (void,
 * dead function with no callers in visible asm). Engine decls
 * mirror staged unanimous views; 4955C's is the least-committal
 * spelling (sibling views disagree on out-param types). */

extern void func_8004914C(void *arg0);
extern void func_800491AC(void *arg0);
extern void *func_80010A08(s32 arg0);
extern void func_80058EB0(void *arg0);
extern s32 func_8004955C(s32 arg0, void *arg1, void *arg2, void *arg3);
extern void func_80058C6C(void *arg0, void *arg1);
extern u8 D_800AF648;
extern u16 D_800B9A02;
extern void *D_800A651C[];

void func_80136D08(s32 arg0, s32 arg1) {
    u8 *s1;
    s32 r1;
    s32 r2;
    s32 s0v;
    u16 v1;
    s32 o1;
    s32 o2;

    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    s1 = func_80010A08(0x14);
    func_80058EB0(s1);
    s1[0xE] = 0xFF;
    s1[4] = 0xFF;
    s1[0xD] = 0x80;
    s1[5] = 0x80;
    s1[0xC] = 0x80;
    s1[6] = 0x80;
    r1 = func_8004955C(arg0, s1 + 8, &o1, &o2);
    r2 = func_8004955C(arg1, s1 + 0x10, &o1, &o2);
    s0v = (r1 + r2) >> 3;
    v1 = D_800B9A02;
    func_80058C6C((u8 *) D_800A651C[v1 * 5] + (s0v << 2), s1);
}

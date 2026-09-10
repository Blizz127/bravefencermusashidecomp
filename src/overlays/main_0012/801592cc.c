/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_801399F0();
void func_80139914();
void *func_8013767C();
void func_80146C98();
extern s32 D_80110C3C;
typedef struct Inner { u8 pad[0x12]; u16 a; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; u8 pad24[0x174]; void *p198; } T;
void func_801592CC(T *p) {
    Inner *in = p->inner;
    in->a = (in->a + 0x16) & 0xFFF;
    if (func_801399F0(p->p198)) {
        func_80139914(p->p198);
        p->p198 = func_8013767C(&D_80110C3C);
        func_80146C98(p, 9);
    }
}

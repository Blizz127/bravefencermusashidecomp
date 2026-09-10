/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8005C604();
extern s32 D_80073B48;
typedef struct { u8 pad[0x14]; s32 a, b, c; } T;
void func_80053144(T *p) {
    func_8005C604(&D_80073B48, p->a, p->b, p->c);
}

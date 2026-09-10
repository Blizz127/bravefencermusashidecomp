/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8014C050();
void func_80146C3C();
void func_80146A6C();
extern s32 D_80126B58;
typedef struct { u8 pad[0x7C]; s16 a, b, c; } T;
void func_8016BA68(T *p, s32 a1) {
    s32 v = func_8014C050(&D_80126B58, 0x56);
    if (v) {
        func_80146C3C(v);
    }
    func_80146A6C(0x56, p, p->a, p->b, p->c, a1, 0);
}

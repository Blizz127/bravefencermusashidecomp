/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_801809B0;
void func_80154150();
void func_80146DB8();
void func_80161CD0();
typedef struct { u8 pad_0[366]; u16 f16E; } T;
void func_8015AC48(T *p) {
    func_80154150(p, 9);
    func_80146DB8(p, &D_801809B0);
    func_80161CD0(p, p->f16E);
}

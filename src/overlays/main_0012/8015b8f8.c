/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801542DC();
void func_80154150();
extern s32 D_800D4A9C;
extern s32 D_800D4B48;
typedef struct { u8 pad[0x23C]; void *p23c; u8 pad240[4]; u8 u244; } T;
void func_8015B8F8(T *p) {
    if (p->p23c == &D_800D4A9C || p->p23c == &D_800D4B48) {
        func_801542DC(p, p->p23c, p->u244);
    } else {
        func_80154150(p, 0xF);
    }
}

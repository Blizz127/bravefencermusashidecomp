/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801477E8();
void func_80171A1C();
extern s16 D_80126B40;
extern s16 D_80126B32;
typedef struct { u8 pad[0x44]; s32 flags; } T;
void func_801735EC(T *p) {
    if (D_80126B40) {
        p->flags |= 0x40000;
    }
    func_801477E8(p, D_80126B32 << 16);
    func_80171A1C(p);
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801599A4();
void func_80159B3C();
void func_80161208();
typedef struct { u8 pad[0x44]; s32 flags; u8 pad48[0x70]; u16 f; } T;
void func_80158548(T *p) {
    p->flags |= 2;
    if (p->f & 0x8000) {
        func_801599A4(p);
        func_80159B3C(p);
    } else {
        func_80161208(p);
    }
}

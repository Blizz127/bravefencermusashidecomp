/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80162CCC();
void func_80165124();
void func_801651B8();
typedef struct { u8 pad[0x62]; s16 f; } T;
void func_801650C4(T *p) {
    p->f -= 0x10;
    if (p->f < 0) {
        func_80162CCC(p);
    } else {
        func_80165124(p);
        func_801651B8(p);
    }
}

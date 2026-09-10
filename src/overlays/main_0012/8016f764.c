/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171928();
typedef struct { u8 pad[0x200]; s32 t; } T;
void func_8016F764(T *p) {
    p->t--;
    if (p->t == -1) {
        func_80171928(p);
    }
}

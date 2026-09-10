/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80168828();
void func_80146C3C();
typedef struct { u8 pad[0x1C]; s32 t; } T;
void func_801687CC(T *p) {
    if (p->t < 3) {
        func_80168828(p);
        p->t++;
    } else {
        func_80146C3C(p);
    }
}

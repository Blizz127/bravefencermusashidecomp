/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80169228();
void func_800D22E4();
void func_80146C3C();
typedef struct { u8 pad[0x14]; s32 u14; u8 pad18[4]; s32 u1c; } T;
void func_801691B8(T *p) {
    if (p->u1c < 10) {
        func_80169228();
        func_800D22E4(p);
        p->u14 += 0x10000;
        p->u1c++;
    } else {
        func_80146C3C(p);
    }
}

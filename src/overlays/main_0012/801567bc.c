/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8014C568();
extern s32 D_801151E0[];
extern s32 D_8011DAD8[];
typedef struct { u8 pad[0x12]; s16 u12; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_801567BC(T *p) {
    u32 i;
    for (i = 0; i < 3; i++) {
        if (D_801151E0[i] & 1) {
            p->inner->u12 = func_8014C568(p, &D_8011DAD8[i * 2]);
        }
    }
}

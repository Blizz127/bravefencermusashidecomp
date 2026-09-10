/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80012B04();
void func_80171928();
extern s16 D_8011F738;
typedef struct Inner { u8 pad[0x12]; s16 a; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_801701C8(T *p) {
    s32 d = func_80012B04(p->inner->a, D_8011F738, 4);
    if ((s16)d == 0) {
        func_80171928(p);
    }
    p->inner->a = (p->inner->a + d) & 0xFFF;
}

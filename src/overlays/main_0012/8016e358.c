/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800D22E4();
void func_8016E460();
void func_80146C3C();
typedef struct {
    u8 pad[0x16]; s16 u16; u8 pad18[4]; s32 t;
    u8 pad20[0x10]; s32 u30;
} T;
void func_8016E358(T *p) {
    p->t--;
    if (p->t != 0) {
        func_800D22E4(p);
        p->u16 -= 3;
        p->u30 -= 0xE;
        func_8016E460(p, (u8 *)p + 0x38);
    } else {
        func_80146C3C(p);
    }
}

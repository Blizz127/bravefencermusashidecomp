/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80078E98;
void func_80166244();
typedef struct { u8 pad[0x1C8]; s16 f; } T;
void func_8014B4D4(T *p) {
    p->f = 0;
    D_80078E98 = 0x80000000;
    func_80166244(p);
}

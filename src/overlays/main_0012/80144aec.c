/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80144B14();
typedef struct { s16 a, b; u8 pad4[0xC8]; s32 cc; u8 padD0[0xC]; s32 dc; } T;
void func_80144AEC(T *p) {
    s32 v = p->dc;
    p->dc = (s32)func_80144B14;
    p->a = 0x83;
    p->b = 1;
    p->cc = v;
}

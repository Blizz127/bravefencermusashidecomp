/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80146CA0();
void func_80165124();
void func_801651B8();
typedef struct { u8 pad[0x62]; s16 u62; } T;
void func_80165064(T *p) {
    s16 v = p->u62 + 16;
    p->u62 = v;
    if (v >= 256) {
        p->u62 = 255;
        func_80146CA0(p);
    }
    func_80165124(p);
    func_801651B8(p);
}

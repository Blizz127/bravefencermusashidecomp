/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80029178();
s32 func_8016F1AC();
void func_80139914();
void func_80029124();
typedef struct { u8 pad[0x198]; void *u198; } T;
void func_8014C99C(T *p) {
    if (func_80029178(0x119) & 0xFF) {
        if (func_8016F1AC()) {
            func_80139914(p->u198);
            p->u198 = 0;
            func_80029124(0x119, 0);
        }
    }
}

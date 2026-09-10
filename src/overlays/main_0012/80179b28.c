/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80139914();
typedef struct { void *u0; s16 u4; } T;
void func_80179B28(T *p) {
    if (p && p->u0 && p->u4 && p->u4 != 0xE) {
        func_80139914(p);
    }
}

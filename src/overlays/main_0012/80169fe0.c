/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80128ED8();
void func_80146C3C();
typedef struct { u8 pad[0x20]; void *inner; } T;
void func_80169FE0(T *p) {
    if (func_80128ED8(p->inner, (u8 *)p + 0x24)) {
        func_80146C3C(p);
    }
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80059A80();
typedef struct { u8 pad[8]; s32 u8, uC; } T;
void func_80146014(T *p) {
    while (p->uC) {
        func_80059A80(p, p->u8, p->uC);
        p = (T *)((u8 *)p + 0x10);
    }
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800D0C48();
void func_800167B8();
typedef struct { u8 pad[0x15]; u8 u15; u8 pad16[0x12]; s32 u28; } T;
s32 func_801623B8(T *p) {
    p->u28 = p->u28 - 1;
    if (p->u28 == -1) {
        func_800D0C48(1);
        func_800167B8(4);
        p->u15 = p->u15 + 1;
    }
    return 0;
}

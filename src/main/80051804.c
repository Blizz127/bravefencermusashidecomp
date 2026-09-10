/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80051844();
void func_80051B0C();
typedef struct { u8 pad[0x18]; s32 f; } U;
void func_80051804(void *p, U *q) {
    if (q->f) {
        func_80051844(p, q);
    } else {
        func_80051B0C(p, q);
    }
}

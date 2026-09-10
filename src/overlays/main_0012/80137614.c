/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_801399A8();
void func_801377B4();
typedef struct { u8 pad[0x1C]; s16 f; } S;
void *func_80137614(void *p, s16 a1, s32 a2) {
    S *s = func_801399A8(p);
    if (s) {
        func_801377B4(p, a2 & 0xD8, s);
        s->f = a1;
    }
    return s;
}

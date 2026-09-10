/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_801399F0();
void func_80139914();
void func_80171928();
typedef struct { u8 pad[0x198]; s32 p198; } T;
void func_80170068(T *p) {
    if (func_801399F0(p->p198)) {
        func_80139914(p->p198);
        p->p198 = 0;
        func_80171928(p);
    }
}

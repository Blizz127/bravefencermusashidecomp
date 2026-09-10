/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154AB4();
typedef struct { u8 pad[0xCC]; s32 *cc; s32 d0; } T;
void func_80154A74(T *p, s32 a1) {
    if (p->d0 != p->cc[a1]) {
        func_80154AB4(p, a1);
    }
}

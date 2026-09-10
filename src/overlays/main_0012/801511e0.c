/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80151204();
typedef struct { u8 pad[0xF2]; s16 f; } T;
void func_801511E0(T *p) {
    func_80151204(p, p->f);
}

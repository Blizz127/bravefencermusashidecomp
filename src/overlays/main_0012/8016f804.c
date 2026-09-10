/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171928();
typedef struct { u8 pad[0x1C2]; u8 f; } T;
void func_8016F804(T *p) {
    if (p->f) {
        p->f = 0;
        func_80171928(p);
    }
}

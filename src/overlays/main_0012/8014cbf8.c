/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct Q { u16 id; u8 pad2[0x72]; u8 u74; } Q;
typedef struct { u8 pad[0x174]; Q *u174; } T;
void func_8014CBF8(T *p) {
    Q *q = p->u174;
    if (q && q->id) {
        p->u174 = 0;
        q->u74 = 0;
    }
}

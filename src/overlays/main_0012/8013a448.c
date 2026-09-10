/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8013A530();
typedef struct Q { u8 pad[0x28]; u16 u28, u2A; } Q;
typedef struct {
    u16 u0, u2;
    Q *q;
} T;
void func_8013A448(T *p) {
    Q *q = p->q;
    if (p->u2 == 0) {
        q->u2A = 0x400;
        q->u28 = 0x400;
        p->u2++;
    } else {
        q->u28 += 0x200;
        q->u2A += 0x200;
        if ((s16)q->u28 == 0x1000) {
            p->u0 = 2;
            p->u2 = 0;
        }
    }
    func_8013A530(p);
}

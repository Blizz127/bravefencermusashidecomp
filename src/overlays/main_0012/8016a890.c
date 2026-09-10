/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016A8FC();
void func_80146C3C();
typedef struct { u16 id; } Q;
typedef struct {
    u8 pad[0x1C]; s32 u1C;
    u8 pad20[0x14]; Q *u34;
} T;
void func_8016A890(T *p) {
    Q *q = p->u34;
    if (p->u1C < 4) {
        if (q->id == 0x14) {
            func_8016A8FC(p);
            p->u1C = p->u1C + 1;
            return;
        }
    }
    func_80146C3C(p);
}

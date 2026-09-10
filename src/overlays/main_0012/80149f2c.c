/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_80144A04();
void func_801599A4();
void func_80159B3C();
void func_8016EDEC();
typedef struct { u16 id; } S;
s32 func_80149F2C(void *p, S *s) {
    void *q;
    if (s->id != 0x83 && s->id != 0x61) {
        return 0;
    }
    q = func_80144A04(s);
    if (q == 0) {
        return 0;
    }
    func_801599A4(p);
    func_80159B3C(p);
    func_8016EDEC(q, 0x1000000);
    return 1;
}

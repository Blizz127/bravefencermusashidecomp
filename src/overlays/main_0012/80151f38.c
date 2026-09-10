/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80149020();
void func_80151FB4();
void func_80159B3C();
void func_80165718();
void func_80172630();
typedef struct { u8 pad[0x64]; s16 u64; u8 pad66[0x78]; u8 de; } T;
void func_80151F38(T *p) {
    func_80149020(p);
    p->u64 -= p->de << 6;
    p->de += 8;
    if (p->u64 < 0x1000) {
        func_80151FB4(p);
        func_80159B3C(p);
        func_80165718(p);
    } else {
        func_80172630(p);
    }
}

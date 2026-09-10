/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80139A8C();
void func_80139B18();
void func_80138B88();
typedef struct { u8 pad[8]; s32 u8; u8 uC; } T;
void func_8013A250(T *p) {
    if (p->uC != 0) {
        p->uC = p->uC - 1;
        func_80139A8C(p);
        if ((p->u8 & 0x80020) == 0) {
            func_80139B18(p);
            return;
        }
    }
    func_80138B88(p);
}

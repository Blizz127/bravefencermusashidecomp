/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80138DB8();
void func_80138B88();
extern void *D_80127524;
typedef struct { u8 pad[8]; s32 u8; } T;
void func_8013A1E8(T *a0) {
    T *p = D_80127524;
    if (p != a0) {
        return;
    }
    if ((func_80138DB8(p, 0, 0x70) << 16) == 0) {
        if ((p->u8 & 0x800) == 0) {
            return;
        }
    }
    func_80138B88(p);
}

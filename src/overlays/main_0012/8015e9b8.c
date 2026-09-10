/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80160818();
void func_80154150();
void func_80149034();
void func_801553A8();
s32 func_80149184();
void func_80146CA0();
extern u8 D_80078EC0;
extern s16 D_801152A0;
typedef struct { u8 pad[0x44]; s32 flags; } T;
void func_8015E9B8(T *p) {
    if (D_80078EC0 & 0x80) {
        func_80160818();
        return;
    }
    func_80154150(p, 0x1D);
    p->flags |= 1;
    func_80149034(p);
    func_801553A8(p);
    D_801152A0 = func_80149184(p);
    func_80146CA0(p);
}

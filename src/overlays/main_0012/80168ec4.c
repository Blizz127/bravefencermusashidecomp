/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80168F40();
void func_800D22E4();
void func_80146C3C();
typedef struct {
    u8 pad[6]; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
    s16 u10; u8 pad12[2]; s16 u14; u8 pad16[2]; s16 u18;
    s32 u1c;
} T;
void func_80168EC4(T *p) {
    if (p->u1c < 5) {
        func_80168F40();
        p->u10 = p->u6;
        p->u14 = p->uA;
        p->u18 = p->uE;
        func_800D22E4(p);
        p->u1c++;
    } else {
        func_80146C3C(p);
    }
}

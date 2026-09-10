/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
void func_8016007C();
void func_80147078();
void func_80159B70();
void func_8014BFF4();
void func_80146CA0();
extern s32 D_800AE6B0;
typedef struct {
    u16 idx;
    u8 pad2[0xBC]; u8 uBE, uBF;
    u8 padC0[0xC4]; s32 u184;
    u8 pad188[0xF]; u8 u197;
    u8 pad198[8]; u8 u1A0;
} T;
void func_8015FCC8(T *p) {
    if (D_800AE6B0 & 0x80FFFFFF) {
        func_8016007C();
        D_80180A1C[p->idx](p);
        func_80147078(p, 0);
        func_80159B70(p);
    } else {
        p->u197 = 0;
        p->uBE = 0;
        p->uBF = 0;
        p->u1A0 = p->u184;
        func_8014BFF4(p, 1);
        func_80146CA0(p);
    }
}

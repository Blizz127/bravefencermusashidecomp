/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80165124();
void func_80146CA0();
extern s32 D_801843A4;
typedef struct {
    u8 pad[0x2C]; s16 u2c, u2e;
    u8 pad30[0x30]; s16 u60, u62;
    u8 pad64[2]; s16 u66;
} T;
void func_80164EE0(T *p) {
    s32 i;
    for (i = 0x70; i >= 0; i -= 0x10) {
        *(s32 *)((u8 *)&D_801843A4 + i) = 0;
    }
    p->u2e = 0x4000;
    p->u2c = 0x4000;
    p->u60 = 0;
    p->u62 = 0;
    func_80165124(p);
    p->u66 = 0;
    func_80146CA0(p);
}

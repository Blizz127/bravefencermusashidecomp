/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
void func_80147078();
void func_80159B70();
void func_80154150();
void func_80154A74();
void func_80146A6C();
void func_80147324();
void func_801553A8();
void func_801553C0();
void func_80146CA0();
extern u8 D_80078EC1;
extern s16 D_801270C0;
extern u8 D_800B9A17;
typedef struct { u16 idx; u8 pad[0x182]; s32 u184; } T;
void func_8015FBE0(T *p) {
    if (p->u184 < 0) {
        D_80180A1C[p->idx](p);
        func_80147078(p, 0);
        func_80159B70(p);
    } else {
        D_80078EC1 = 0;
        func_80154150(p, 0x20);
        func_80154A74(p, 0x18);
        func_80146A6C(0x16, p, 0, 0, 0, 0, 0);
        func_80147324(0x44F);
        func_801553A8(p);
        func_801553C0(p);
        D_801270C0 = 2;
        D_800B9A17 = 0;
        func_80146CA0(p);
    }
}

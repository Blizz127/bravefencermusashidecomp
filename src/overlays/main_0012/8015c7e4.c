/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
s32 func_80161B18();
s32 func_80161B84();
s32 func_801496D4();
void func_80149704();
s32 func_801487F4();
s32 func_801488A8();
void func_80147078();
void func_80159B70();
s32 func_80161240();
s32 func_80146E98();
void func_80148AAC();
void func_80146DB8();
void func_80146E90();
void func_80146CA0();
void func_80161C24();
void func_8014C010();
extern s32 D_801809C0;
typedef struct {
    u16 idx;
    u8 pad2[0xB6]; u16 b8;
    u8 padBA[0xB4]; u16 u16E;
} T;
void func_8015C7E4(T *p) {
    if (func_80161B18(p)) {
        return;
    }
    if (func_80161B84(p)) {
        return;
    }
    if (func_801496D4(p)) {
        D_80180A1C[p->idx](p);
        func_80149704(p);
        return;
    }
    if ((func_801487F4(p) & 0x80) == 0 && func_801488A8(p) == 0) {
        D_80180A1C[p->idx](p);
        func_80147078(p, 0);
        func_80159B70(p);
        return;
    }
    if (func_80161240(p)) {
        return;
    }
    if (func_80146E98(p)) {
        func_80148AAC(p);
        func_80146DB8(p, &D_801809C0);
        func_80146E90(p, 0x14);
        func_80146CA0(p);
    }
    if (p->b8 & 0x2000) {
        func_80161C24(p, p->u16E);
        func_8014C010(p, 2);
    }
}

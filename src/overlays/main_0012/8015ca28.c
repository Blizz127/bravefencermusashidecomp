/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
void func_80149FB0();
s32 func_80161B18();
s32 func_80161B84();
s32 func_801496D4();
void func_80149704();
s32 func_801487F4();
s32 func_801488A8();
s32 func_80148AAC();
void func_80147AD4();
void func_801473EC();
s32 func_8014D738();
void func_80146DB8();
void func_80146E90();
void func_80146C98();
void func_80147078();
void func_80159B70();
void func_80161240();
extern s32 D_801809C0;
typedef struct {
    u16 idx;
    u8 pad2[0x16E]; s32 u170;
} T;
void func_8015CA28(T *p) {
    func_80149FB0(p);
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
    if (func_80148AAC(p) & 0xFF) {
        func_80147AD4(p, 0, 0, 0);
        func_801473EC(p);
    }
    if (func_8014D738(p)) {
        func_80146DB8(p, &D_801809C0);
        func_80146E90(p, 0x14);
        func_80146C98(p, 2);
    }
    if (p->u170 == 0) {
        D_80180A1C[p->idx](p);
        func_80147078(p, 0);
        func_80159B70(p);
    } else {
        func_80161240(p);
    }
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800D4DB4;
void func_80148038();
void func_80147460();
void func_80154274();
void func_80146CA0();
void func_80147324();
typedef struct {
    u8 pad[0x34];
    s32 unk34;
    u8 pad38[0xC];
    u32 flags;
} T;
void func_80155B9C(T *p) {
    p->flags |= 2;
    func_80148038(p, 0x30000);
    func_80147460(p);
    if (p->unk34 >= 0) {
        func_80154274(p, &D_800D4DB4);
        func_80146CA0(p);
        func_80147324(0x447);
    }
}

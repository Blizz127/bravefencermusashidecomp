/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800D52A8;
void func_80154274();
void func_80154A74();
void func_801585A4();
void func_8016706C();
void func_80146994();
void func_80147324();
void func_80146CA0();
typedef struct {
    u8 pad[0x44];
    u32 flags;
    u8 pad48[0x1AA-0x48];
    u8 f1AA;
} T;
void func_801582C0(T *p) {
    p->f1AA = 0x10;
    p->flags |= 2;
    func_80154274(p, &D_800D52A8);
    func_80154A74(p, 0x15);
    func_801585A4(p);
    func_8016706C(5);
    func_80146994(4, p, 8, 0);
    func_80147324(0x446);
    func_80146CA0(p);
}

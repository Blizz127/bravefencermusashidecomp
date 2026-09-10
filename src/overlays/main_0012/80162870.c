/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8001CB6C();
void func_80162968();
void func_80162ACC();
extern s32 D_800B5CB8;
extern s32 D_80180F18;
extern void *D_800B5CEC;
extern u8 D_800B5CDF;
extern s32 D_800B5CBC;
typedef struct { u8 pad[8]; void *p8; } T;
void func_80162870(T *p) {
    p->p8 = &D_800B5CB8;
    func_8001CB6C(&D_800B5CB8, &D_80180F18, 0x250, 0x1A0);
    D_800B5CEC = (u8 *)p + 0xC;
    D_800B5CDF = 0x14;
    D_800B5CBC |= 0x60000000;
    func_80162968(p);
    func_80162ACC(p);
}

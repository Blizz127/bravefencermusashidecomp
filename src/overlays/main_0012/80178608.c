/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80016714();
void func_8013E4B4();
extern s32 D_801202A0;
typedef struct {
    s16 a, b, c; u8 d, e;
} S;
extern S D_801270C0;
extern s32 D_801274D8, D_801274DC, D_801274E0;
void func_80178608(void) {
    func_80016714(&D_801202A0, 0x6480);
    D_801270C0.a = 1;
    D_801270C0.c = 1;
    D_801274D8 = 0x240000;
    D_801270C0.b = 0;
    D_801270C0.d = 0;
    D_801270C0.e = 0;
    D_801274DC = 0x271000;
    D_801274E0 = 0x400000;
    func_80016714((u8 *)&D_801270C0 + 8, 0x400);
    func_8013E4B4();
}

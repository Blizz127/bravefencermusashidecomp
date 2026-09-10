#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80129248();                                 /* static */
void func_80146CA0(s32);                               /* static */
void func_80146E90(s32, s32);                            /* static */
void func_80149020();                                  /* static */
void func_80154150(s32, s32);                            /* static */
void func_80154A74(s32, s32);                            /* static */
extern s8 D_800B9A17;
extern s16 D_801270C0;

void func_80160F00(s32 arg0) {
    func_80149020();
    func_80154150(arg0, 4);
    func_80154A74(arg0, 0x11);
    D_801270C0 = 2;
    func_80129248(0);
    D_800B9A17 = 0;
    func_80146E90(arg0, 0x10);
    func_80146CA0(arg0);
}

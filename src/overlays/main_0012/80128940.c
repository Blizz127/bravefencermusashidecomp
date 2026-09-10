/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8001ABBC();
typedef struct { s32 a; void *b; } S;
extern S D_800C7C60;
extern s32 D_800A2E20;
extern void *D_80182D1C;
extern s32 D_800AF560;
void func_80128940(void) {
    D_800C7C60.a = 94;
    D_800C7C60.b = &D_800A2E20;
    func_8001ABBC(0, 0, &D_800AF560, D_80182D1C, &D_800C7C60);
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800153CC();
extern s16 D_80126B5E;
extern s16 D_80126B62;
extern s16 D_80126B66;
extern u16 D_80126CC4;
typedef struct { u8 pad[0x12]; s16 u12; } S;
extern S *D_80126B78;
void func_80136DFC(void) {
    func_800153CC(0xA, D_80126B5E, 0x110, 0x3C, 4, 0);
    func_800153CC(0xB, D_80126B62, 0x110, 0x44, 4, 0);
    func_800153CC(0xC, D_80126B66, 0x110, 0x4C, 4, 0);
    func_800153CC(0xD, D_80126B78->u12, 0x110, 0x54, 4, 0);
    func_800153CC(0xE, D_80126CC4, 0x110, 0x5C, 4, 0);
}

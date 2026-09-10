/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80172358();
extern s32 D_80126B58;
typedef struct { u8 pad[6]; u16 unk6; } T;
typedef struct { u8 pad[0x12]; u16 unk12; } G;
extern G *D_80126B78;
void func_80172310(T *p) {
    func_80172358(&D_80126B58, p);
    D_80126B78->unk12 = p->unk6;
}

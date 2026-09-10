/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80145BF8();
void func_80146CA0();
extern s32 D_80184288;
extern s32 D_80184290;
extern u8 D_800AE6BD;
typedef struct Inner { u8 pad[0x12]; u16 u12; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_8015934C(T *p) {
    Inner *in;
    if (D_80184288 == 4) {
        D_80184288 = 5;
    }
    if (D_80184290) {
        func_80145BF8();
        func_80146CA0(p);
        D_800AE6BD = D_800AE6BD + 1;
    }
    in = p->inner;
    in->u12 = (in->u12 + 0x16) & 0xFFF;
}

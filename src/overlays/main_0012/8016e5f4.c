/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80015978();
s32 func_8012EFB8();
void func_80146C3C();
void func_80015954();
typedef struct { u8 pad[2]; u16 u2; u8 pad4[0xC]; s16 u10, u12, u14, u16; } T;
void func_8016E5F4(T *p) {
    s16 tmp[4];
    func_80015978((u8 *)p + 4, tmp);
    if (func_8012EFB8(tmp, tmp) & ~0x1000) {
        func_80146C3C(p);
    } else {
        func_80015954(tmp, (u8 *)p + 4);
        p->u10 = 0x100;
        p->u12 = 0;
        p->u14 = 0;
        p->u16 = 0x80;
        p->u2++;
    }
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016E778();
typedef struct {
    u8 pad[2]; u16 u2;
    u8 pad4[0xC]; u16 u10, u12;
    u8 pad14[8]; s32 u1C;
} T;
void func_8016E688(T *p) {
    p->u10 = p->u10 + 0x200;
    p->u12 = p->u12 + p->u10;
    if ((s16)p->u12 >= 0x3000) {
        p->u1C = 4;
        p->u2 = p->u2 + 1;
    }
    func_8016E778(p);
}

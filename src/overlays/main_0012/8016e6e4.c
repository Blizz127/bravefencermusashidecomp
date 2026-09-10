/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016E778();
typedef struct {
    u8 pad[2]; u16 u2;
    u8 pad4[0x18]; s32 u1C;
} T;
void func_8016E6E4(T *p) {
    p->u1C = p->u1C - 1;
    if (p->u1C == -1) {
        p->u2 = p->u2 + 1;
    }
    func_8016E778(p);
}

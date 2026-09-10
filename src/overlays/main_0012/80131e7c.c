/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8012E470();
void func_8012E4C8();
void func_80131E00();
void func_80131CA8();
typedef struct { u8 pad[0xB4]; s32 uB4; } T;
void func_80131E7C(T *p) {
    if (p->uB4 & 0x40000) {
        if (func_8012E470(p)) {
            func_8012E4C8(p);
            func_80131E00(p, 1);
        }
    }
    func_80131CA8(p, 0x3A);
}

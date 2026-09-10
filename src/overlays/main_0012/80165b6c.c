/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80161104();
void func_80165BB4();
typedef struct { u8 pad[0x197]; u8 unk197; } T;
void func_80165B6C(T *p) {
    if (func_80161104(p)) {
        func_80165BB4(p);
        p->unk197++;
    }
}

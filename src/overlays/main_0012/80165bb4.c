/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154150();
void func_80154A74();
typedef struct {
    u8 pad_0[407];
    u8 idx;
} T;
void func_80165BB4(T *p) {
    func_80154150(p, 34);
    func_80154A74(p, 26);
    p->idx += 1;
}

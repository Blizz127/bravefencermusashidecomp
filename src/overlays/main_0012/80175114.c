/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147078();
void func_80175184();
typedef struct {
    u8 pad_0[2];
    s16 f2;
} T;
void func_80175114(T *p) {
    func_80147078(p, 8);
    p->f2 = 1;
    func_80175184(p);
}

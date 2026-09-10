/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801653F4();
void func_80147078();
void func_80165580();
typedef struct {
    u8 pad_0[407];
    u8 f197;
} T;
void func_80165374(T *p) {
    func_801653F4(p);
    func_80147078(p, 23);
    p->f197 = 1;
    func_80165580(p);
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80161D20();
void func_8014C010();
typedef struct {
    u8 pad_0[366];
    u16 f16E;
} T;
void func_80157A8C(T *p) {
    func_80161D20(p, p->f16E);
    func_8014C010(p, 1);
}

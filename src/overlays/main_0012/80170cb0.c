/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801719A4();
void func_8017197C();
void func_80170CF0();
typedef struct {
    u8 pad_0[535];
    u8 f217;
} T;
void func_80170CB0(T *p) {
    func_801719A4(p, 3);
    p->f217 = 0;
    func_8017197C(p);
    func_80170CF0(p);
}

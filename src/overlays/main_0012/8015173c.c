/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014C8F0();
void func_80147078();
void func_80151780();
typedef struct {
    u16 f0;
    u8 pad_2[220];
    u8 fDE;
} T;
void func_8015173C(T *p) {
    func_8014C8F0(p);
    p->fDE = (u8) p->f0;
    func_80147078(p, 25);
    func_80151780(p);
}

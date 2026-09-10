/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80149020();
void func_801470B4();
void func_8015369C();
void func_80146CA0();
typedef struct {
    u8 pad[0x60]; s16 a, b, c;
    u8 pad66[0x78]; u8 de;
} T;
void func_80153150(T *p) {
    s16 v;
    func_80149020(p);
    v = p->c - 0x100;
    p->c = v;
    p->b = v;
    p->a = v;
    if (v <= 0) {
        p->de = 0x10;
        func_801470B4(p);
        func_8015369C(p);
        func_80146CA0(p);
    }
}

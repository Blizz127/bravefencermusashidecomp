/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171A1C();
extern s16 D_80126B30;
typedef struct { u8 pad[0xAA]; u16 a, b; } T;
void func_80173980(T *p) {
    if (D_80126B30 == 0) {
        p->b |= 0x80;
        p->a |= 0x80;
    } else {
        p->b |= 0x10;
    }
    func_80171A1C(p);
}

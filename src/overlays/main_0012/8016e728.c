/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80146C3C();
void func_8016E778();
typedef struct { u8 pad[0x12]; u16 a; u8 pad14[2]; s16 b; } T;
void func_8016E728(T *p) {
    p->a += 0x400;
    p->b -= 8;
    if (p->b <= 0) {
        func_80146C3C(p);
    } else {
        func_8016E778(p);
    }
}

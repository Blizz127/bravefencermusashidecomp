/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171EC8();
void func_80146D90();
typedef struct { u8 pad[0x20C]; u8 c; } T;
s32 func_80171C64(T *p, u32 a1) {
    u8 v;
    func_80171EC8(p);
    v = p->c;
    p->c = v + 1;
    if (v == (u8)a1) {
        func_80146D90(p);
        return 1;
    }
    return 0;
}

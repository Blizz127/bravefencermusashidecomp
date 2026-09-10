/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80016714();
typedef struct { u16 kind; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_80162CCC(T *p) {
    if (p->inner) {
        func_80016714(p->inner, p->inner->kind == 1 ? 0x84 : 0x38);
    }
    func_80016714(p, 0x68);
}

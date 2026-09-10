/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80016714();
void func_8012C218();
typedef struct {
    u8 pad_0[204];
    void * ptr;
} T;
void func_801439C0(T *p) {
    if (p) {
        func_80016714(p->ptr, 56);
        func_8012C218(p);
    }
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_8017E338[];
typedef struct {
    u8 pad_0[104];
    s32 idx;
} T;
void func_8013BC7C(T *p) {
    D_8017E338[p->idx](p);
}

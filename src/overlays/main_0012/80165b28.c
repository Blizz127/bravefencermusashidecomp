/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80181254[];
typedef struct { u8 pad[0x44]; u32 flags; u8 pad2[0x197-0x48]; u8 idx; } T;
void func_80165B28(T *p) {
    p->flags |= 8;
    D_80181254[p->idx]();
}

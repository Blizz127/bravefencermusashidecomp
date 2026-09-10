/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80148800();
typedef struct { u8 pad[0x244]; u16 u244; } T;
s32 func_801585AC(T *p) {
    p->u244 = p->u244 | func_80148800(p);
    if (p->u244 & 0x10) {
        return 1;
    }
    return 0;
}

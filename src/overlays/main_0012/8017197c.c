/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x214]; u8 u214, u215, u216; } T;
void func_8017197C(T *p) {
    p->u216 = 0;
    p->u215 = p->u215 + 1;
}

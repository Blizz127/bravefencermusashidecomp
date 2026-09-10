/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80171AB0();
void func_80171928();
typedef struct { u8 pad[0x3C]; s32 a, b, c; } G;
extern G *D_801151D4;
void func_8017044C(void *p) {
    s16 tmp[3];
    G *g = D_801151D4;
    tmp[0] = g->a;
    tmp[1] = g->b;
    tmp[2] = g->c;
    if ((s16)func_80171AB0(p, tmp) == 0) {
        func_80171928(p);
    }
}

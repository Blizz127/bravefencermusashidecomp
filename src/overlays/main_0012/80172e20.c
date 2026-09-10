/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80171AB0();
void func_80171A1C();
void func_80174650();
typedef struct { u8 pad[6]; u16 a; u8 pad8[2]; u16 b; u8 padC[2]; u16 c; } G;
extern G *D_80127508;
void func_80172E20(void *p) {
    s16 tmp[3];
    G *g = D_80127508;
    tmp[0] = g->a;
    tmp[1] = g->b;
    tmp[2] = g->c;
    if ((s16)func_80171AB0(p, tmp) == 0) {
        func_80171A1C(p);
        func_80174650(p);
    }
}

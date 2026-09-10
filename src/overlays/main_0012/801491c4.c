/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8004CFEC();
typedef struct { u8 pad[0x3C]; s32 a, b, c, d, e, f; } G;
extern G *D_801151D4;
s32 func_801491C4(void) {
    G *g = D_801151D4;
    return (s16)func_8004CFEC(g->a - g->d, g->c - g->f);
}

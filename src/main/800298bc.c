/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u32 w[9]; } T_800298BC;
extern T_800298BC D_80079204;
void func_8002992C(s32);
void func_800298BC(T_800298BC *dst) {
    func_8002992C(1);
    *dst = D_80079204;
}

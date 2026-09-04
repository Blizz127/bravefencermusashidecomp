#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80078C6C;
extern s32 D_80078C70;
extern s32 D_80078C74;
extern s32 D_80078C78;

s32 func_80061E54(void) {
    return D_80078C6C + (D_80078C70 * 2) + (D_80078C74 * 4) + (D_80078C78 * 8);
}

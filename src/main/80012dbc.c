/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80012E0C();
s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3) {
    return (a0 + func_80012E0C((s16)a0, (s16)a1, (s16)a2, (s16)a3)) & 0xFFF;
}

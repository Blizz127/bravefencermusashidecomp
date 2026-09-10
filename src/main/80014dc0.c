/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 v; u8 pad[0x4B]; } T_func_80014DC0;
extern T_func_80014DC0 D_80078D98[];
u8 func_80014DC0(u8 i) { return D_80078D98[i].v; }

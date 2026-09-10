/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u16 v; u8 pad[0x4A]; } T_func_80014BFC;
extern T_func_80014BFC D_80078DDA[];
u16 func_80014BFC(u8 i) { return D_80078DDA[i].v; }

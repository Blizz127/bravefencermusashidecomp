/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80029178(s32);
typedef struct { u8 pad[0xAC]; u16 flags; } T;
s32 func_8014A4B4(T *p) {
    s32 v = func_80029178(0x1E);
    if ((v & 0xFF) == 0) return 0;
    if (p->flags & 0x40) return 1;
    return 0;
}

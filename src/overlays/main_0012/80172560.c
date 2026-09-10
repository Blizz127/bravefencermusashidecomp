/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80013450();
typedef struct { u8 pad[0xA]; u16 unkA; } T;
typedef struct { u8 pad[2]; s16 unk2; } U;
s32 func_80172560(T *p, U *q) {
    q->unk2 = p->unkA;
    return func_80013450((u8 *)p + 4) < 0x10;
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x2C]; s32 unk2C; u8 pad2[5]; u8 unk35; u8 unk36; } T;
void func_8005E194(T *p, s32 a1, s32 a2, s32 a3) {
    p->unk36 = a1;
    p->unk2C = a2;
    p->unk35 = a3;
}

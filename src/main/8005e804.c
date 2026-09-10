/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x20]; s32 unk20; u8 pad2[8]; s32 unk2C; u8 pad3[5]; u8 unk35; u8 unk36; } T;
void func_8005E804(T *p) {
    s32 v = p->unk20;
    p->unk36 = 0x4D;
    p->unk35 = 6;
    p->unk2C = v;
}

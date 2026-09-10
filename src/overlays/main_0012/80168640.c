/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[2]; s16 unk2; u8 pad4[0xC]; s16 unk10, unk12; u8 pad14[8]; s32 unk1C; } T;
void func_80168640(T *p) {
    p->unk1C = 0x20;
    p->unk12 = 0;
    p->unk10 = 0x80;
    p->unk2++;
}

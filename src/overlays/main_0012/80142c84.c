/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x14]; s32 a; u8 pad2[0x30]; s32 b; u8 pad3[0xB6]; s16 c; } T;
void func_80142C84(T *p) {
    p->a = 0xFFF40000;
    p->b = 0x20000;
    p->c = 0;
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800DE2A4;
typedef struct { u8 pad[0x44]; s32 flags; } T;
void func_801552F4(T *p) {
    s32 *s = &D_800DE2A4;
    while (*s) {
        *s = *s & 0x80FFFFFF;
        s++;
    }
    p->flags |= 0x30000000;
}

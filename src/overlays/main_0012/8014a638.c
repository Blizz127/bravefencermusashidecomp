/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct {
    u8 pad[0x44]; s32 flags;
    u8 pad48[0x140]; s16 u188;
} T;
void func_8014A638(T *p) {
    if (p->flags & 0x10) {
        p->u188 = p->u188 - 4;
        if (p->u188 < 0) {
            p->u188 = 0;
        }
    }
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u16 id; u8 pad[0x82]; } S;
typedef struct { u8 pad[0x20]; S *inner; } T;
extern u8 D_800B3DF0[];
S *func_8012C1DC(T *p) {
    S *s = (S *)((u8 *)p->inner + 0x84);
    S *end = (S *)D_800B3DF0;
    while (s != end) {
        if (s->id == 0) {
            return s;
        }
        s++;
    }
    return 0;
}

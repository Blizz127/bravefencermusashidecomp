/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u8 D_80120194[];
typedef struct { u16 id; u8 pad[0x10A]; } S;
S *func_8012C31C(void) {
    S *start = (S *)D_80120194;
    S *s = (S *)(D_80120194 + 0x6480);
    while (s != start) {
        if (s->id == 0) {
            return s;
        }
        s--;
    }
    return 0;
}

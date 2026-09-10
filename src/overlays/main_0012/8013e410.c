/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u8 D_801202A0[];
typedef struct { u16 id; u8 pad[0x10A]; } S;
S *func_8013E410(void) {
    S *s;
    s32 i;
    s = (S *)D_801202A0;
    for (i = 0; i < 0x60; i++, s++) {
        if (s->id == 0) {
            return s;
        }
    }
    return 0;
}

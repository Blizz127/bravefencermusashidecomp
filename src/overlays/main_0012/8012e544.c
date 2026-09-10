/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012E544 (main_0012.s), decoded manually from
 * raw asm (0x38 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): same pool scan as
 * func_8012E504 but without the arg0 exclusion: returns the first
 * 0x10C-stride entry from &D_801202A0 (+0x6480 bound) whose first
 * u16 equals arg0, else 0. */

extern u8 D_801202A0;

u8 *func_8012E544(s32 arg0) {
    u8 *v1;
    u8 *end;

    v1 = &D_801202A0;
    end = &D_801202A0 + 0x6480;
    while (v1 != end) {
        if (*(u16 *) v1 == arg0) {
            return v1;
        }
        v1 += 0x10C;
    }
    return 0;
}

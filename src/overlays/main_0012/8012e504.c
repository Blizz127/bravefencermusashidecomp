/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012E504 (main_0012.s), decoded manually from
 * raw asm (0x40 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): scans the 96-entry
 * 0x10C-stride pool from &D_801202A0 to +0x6480, skipping arg0,
 * returning the first entry whose first u16 equals arg1 (lhu/beq;
 * arg1 kept s32 so the comparison is bit-exact), else 0 (NULL is
 * spelled 0: no hosted headers under the Psy-Q chain). */

extern u8 D_801202A0;

u8 *func_8012E504(void *arg0, s32 arg1) {
    u8 *v1;
    u8 *end;

    v1 = &D_801202A0;
    end = &D_801202A0 + 0x6480;
    while (v1 != end) {
        if (v1 != arg0 && *(u16 *) v1 == arg1) {
            return v1;
        }
        v1 += 0x10C;
    }
    return 0;
}

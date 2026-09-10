/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012E57C (main_0012.s), decoded manually from
 * raw asm (0x50 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): pool find-first like
 * func_8012E504 but keyed on two fields: first u16 == arg0 and
 * s16 at +0x70 == arg1 (a1 is sign-extended via sll/sra in the
 * entry-branch delay slot, hence s16). Byte stride 0x10C,
 * +0x6480 bound, else 0. */

extern u8 D_801202A0;

u8 *func_8012E57C(s32 arg0, s16 arg1) {
    u8 *v1;
    u8 *end;

    v1 = &D_801202A0;
    end = &D_801202A0 + 0x6480;
    while (v1 != end) {
        if (*(u16 *) v1 == arg0 && *(s16 *) (v1 + 0x70) == arg1) {
            return v1;
        }
        v1 += 0x10C;
    }
    return 0;
}

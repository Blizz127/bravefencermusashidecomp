/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void func_80016714();
extern u8 D_80184198[];
extern u32 D_801269D4;
extern u32 D_801269C8;

/* HAND MODEL of func_8013C98C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void), O2 leaf
 * (a1 = 8 rides the jal delay slot). Calls
 * func_80016714(&D_80184198, 8) (unprototyped decl mirrors
 * staging/hand/func_8016B984.c), then zeroes D_801269D4 and
 * D_801269C8. Void: no result is consumed. */
void func_8013C98C(void)
{
    func_80016714(D_80184198, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}

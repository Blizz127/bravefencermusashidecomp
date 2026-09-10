/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern s32 func_80019198(void);
extern void func_80019064();
extern u8 D_80184198[];
extern u8 D_80062BC0;

/* HAND MODEL of func_8013C9C4 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void *), O2
 * frame. Stores arg0 into the D_80184198 blob word, zeroes blob
 * bytes +4/+5, then if func_80019198() returns 0 calls
 * func_80019064(&D_80062BC0) (assert-style error string;
 * unprototyped decl mirrors staging/hand/func_8012E9C0.c, whose
 * u8 + &-of-symbol convention is followed here). Pointer arg:
 * the sole caller (func_8015E588) passes &D_80180CF4. Void: v0
 * after the second jal is ignored. */
void func_8013C9C4(void *arg0)
{
    *(void **)D_80184198 = arg0;
    D_80184198[4] = 0;
    D_80184198[5] = 0;
    if (func_80019198() == 0) {
        func_80019064(&D_80062BC0);
    }
}

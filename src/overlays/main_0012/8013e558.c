/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void func_800D24A0();
extern void func_80141788();
extern void (*D_8011DB24)();

/* HAND MODEL of func_8013E558 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void), O2 frame.
 * Calls func_800D24A0(2) (a0 rides the jal delay slot;
 * unprototyped decl: no further arg facts), then vectors the
 * D_8011DB24 callback slot to func_80141788 (unspecified-args
 * funcptr: the slot also takes func_80141874 in func_8013E588, so
 * no firmer signature is claimed). Void: v0 after the jal is
 * ignored. */
void func_8013E558(void)
{
    func_800D24A0(2);
    D_8011DB24 = func_80141788;
}

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern s32 func_800D0EC4(void);
extern void func_80141874();
extern void (*D_8011DB24)();
extern s8 D_800B9A15;
extern s8 D_800B9A13;
extern u8 D_80115110[];
extern s16 D_80115112;

/* HAND MODEL of func_8013E588 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void), O2 frame.
 * When func_800D0EC4() returns 0, stamps the init pattern
 * (D_800B9A15 = 1, D_800B9A13 = 2, D_80115110 word = 1,
 * D_80115112 = 0) and vectors D_8011DB24 to func_80141874.
 * Global decl shapes mirror staging/hand/func_8013E958.c (s8,
 * u8[], s16; D_800B9A13 is sb like its B9A15 sibling). Void: no
 * result is produced. */
void func_8013E588(void)
{
    if (func_800D0EC4() == 0) {
        D_800B9A15 = 1;
        D_800B9A13 = 2;
        *(u16 *)D_80115110 = 1;
        D_80115112 = 0;
        D_8011DB24 = func_80141874;
    }
}

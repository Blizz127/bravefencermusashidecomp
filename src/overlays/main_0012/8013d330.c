/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern u8 D_80185C0A;
extern u8 D_80185C7E;
extern u8 D_80185B32;
extern u8 D_80185BEC;
extern u8 D_80185B10;
extern u8 D_80185B31;
extern u32 D_80185BF0;

/* HAND MODEL of func_8013D330 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void), frameless
 * O2 leaf. Three single-step servos (+-1 toward target, unsigned
 * compare): D_80185C0A toward C7E, D_80185B32 toward BEC,
 * D_80185B10 toward B31; then stamps D_80185BF0 = 1 (the flag
 * func_8013CB84 clears on entry). Sibling stepper with +-8 steps
 * is func_8013D178. */
void func_8013D330(void)
{
    if (D_80185C0A != D_80185C7E) {
        if (D_80185C0A < D_80185C7E) {
            D_80185C0A++;
        } else {
            D_80185C0A--;
        }
    }
    if (D_80185B32 != D_80185BEC) {
        if (D_80185B32 < D_80185BEC) {
            D_80185B32++;
        } else {
            D_80185B32--;
        }
    }
    if (D_80185B10 != D_80185B31) {
        if (D_80185B10 < D_80185B31) {
            D_80185B10++;
        } else {
            D_80185B10--;
        }
    }
    D_80185BF0 = 1;
}

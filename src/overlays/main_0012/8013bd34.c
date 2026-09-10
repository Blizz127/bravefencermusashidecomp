/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void func_8013BD74(u8 *arg0, u8 *arg1);
extern u8 D_80185C10[];

/* HAND MODEL of func_8013BD34 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * fp-frame. Thin wrapper: func_8013BD74(&D_80185C10, arg0). Void:
 * v0 after the jal is ignored. */
void func_8013BD34(u8 *arg0)
{
    func_8013BD74(D_80185C10, arg0);
}

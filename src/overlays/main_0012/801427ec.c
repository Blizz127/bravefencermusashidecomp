/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void (*D_8017F7C8[])(void *arg0);
extern s16 D_801270C0;

/* HAND MODEL of func_801427EC (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame (ra saved only on the taken path, via the beq delay slot).
 * Returns at once when lh(D_801270C0) == 3; otherwise indirect
 * tail-calls F7C8[lhu(a0+2)] with a0. Table element type
 * provisional. */
void func_801427EC(u8 *arg0)
{
    if (D_801270C0 == 3) {
        return;
    }
    D_8017F7C8[*(u16 *)(arg0 + 2)](arg0);
}

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void (*D_8017FD00[])(void *arg0);

/* HAND MODEL of func_80143E68 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame. Indirect tail-call of FD00[lhu(a0+2)] with a0 (which
 * still holds the incoming pointer across the nop delay slot).
 * The three trailing jr ra pairs are padding. Table element type
 * provisional. */
void func_80143E68(u8 *arg0)
{
    D_8017FD00[*(u16 *)(arg0 + 2)](arg0);
}

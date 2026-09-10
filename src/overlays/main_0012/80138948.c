/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80138948 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * no frame. h04 = 7, b1F = 0, b0D = 0 (both sb's ride delay
 * slots and always execute). */

struct st_80138948 {
    u8 pad00[4];
    u16 h04;
    u8 pad06[7];
    u8 b0D;
    u8 pad0E[0x11];
    u8 b1F;
};

void func_80138948(struct st_80138948 *arg0) {
    arg0->h04 = 7;
    arg0->b1F = 0;
    arg0->b0D = 0;
}

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801375EC (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): dead tail-call
 * adapter, 0x18 frame. Returns func_80137614(a0, (s16)a1, 0)
 * (a0 live, a1 half-signed via sll/sra, a2 = 0 in the jal delay
 * slot). No callers in visible asm; the pointer result flows
 * straight through per the callee's model. */

struct opq_801375EC {
    u8 pad[0x1C];
    u16 h1C;
};

extern struct opq_801375EC *func_80137614(void *arg0, s32 arg1, s32 arg2);

struct opq_801375EC *func_801375EC(void *arg0, s32 arg1) {
    return func_80137614(arg0, (s16) arg1, 0);
}

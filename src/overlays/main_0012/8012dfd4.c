/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012DFD4 (main_0012.s), decoded manually from
 * raw asm (0x40 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): dispatches on the
 * byte at arg0 + 0x74 (lbu, not a word load) to func_8012E014
 * (nonzero) or func_8012E138 (zero); both jals carry no new
 * arguments in delay slots. Shared func_8012E004 epilogue. */

struct obj_8012DFD4 {
    u8 pad[0x74];
    u8 unk74;
};

extern void func_8012E014(void);
extern void func_8012E138(void);

void func_8012DFD4(struct obj_8012DFD4 *arg0) {
    if (arg0->unk74 != 0) {
        func_8012E014();
    } else {
        func_8012E138();
    }
}

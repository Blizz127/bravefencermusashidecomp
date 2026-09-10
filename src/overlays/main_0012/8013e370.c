/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

struct src_8012C724;
extern u8 *func_8013E410(void);
extern s32 func_8013E448(u8 *arg0);
extern void func_8012C724(struct src_8012C724 *arg0, void *arg1);
extern u8 *D_801274CC;

/* HAND MODEL of func_8013E370 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void), O2 frame.
 * Walks the D_801274CC 0x14-stride record list while each
 * record's +6 halfword stays nonzero: records whose +10 halfword
 * carries 0x8000 are skipped, otherwise a free slot from
 * func_8013E410 (NULL slot aborts the whole walk) is paired with
 * the record through func_8013E448, and a nonzero dispatch result
 * additionally runs func_8012C724(record, slot) (struct decl owned
 * by staging/hand/func_8012C724.c, forward-declared here). Void:
 * no result is produced. */
void func_8013E370(void)
{
    u8 *s0;
    u8 *s2;
    u8 *s1;

    s0 = D_801274CC;
    if (s0 == 0) {
        return;
    }
    s2 = s0 + 6;
    if (*(u16 *)s2 == 0) {
        return;
    }
    do {
        if (!(*(u16 *)(s2 + 4) & 0x8000)) {
            s1 = func_8013E410();
            if (s1 == 0) {
                return;
            }
            if (func_8013E448(s0) != 0) {
                func_8012C724((struct src_8012C724 *)s0, s1);
            }
        }
        s2 += 0x14;
        s0 += 0x14;
    } while (*(u16 *)s2 != 0);
}

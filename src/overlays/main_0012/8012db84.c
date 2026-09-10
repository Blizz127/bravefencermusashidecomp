/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012DB84 (main_0012.s), decoded manually from
 * raw asm (19 instructions; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): calls func_8014C978,
 * then func_8012F568(1, 0xC001, 0, 0x3E8, &D_8017E6C4, &D_8017E6CC).
 * The two stack slots (0x10/0x14) are the 5th/6th call arguments,
 * and the lui/addiu pairs take the addresses of D_8017E6C4/D_8017E6CC,
 * matching the (s32, s32, s32, void *, void *, void *) prototype
 * already established by func_8012D664. */

extern void func_8014C978(void);
extern u8 D_8017E6C4;
extern u8 D_8017E6CC;
extern s32 func_8012F568(s32 arg0, s32 arg1, s32 arg2, void *arg3, void *arg4, void *arg5);

void func_8012DB84(void) {
    func_8014C978();
    func_8012F568(1, 0xC001, 0, (void *) 0x3E8, &D_8017E6C4, &D_8017E6CC);
}

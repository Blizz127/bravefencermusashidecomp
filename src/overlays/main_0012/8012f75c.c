/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F75C (main_0012.s), decoded manually from
 * raw asm (0x58 bytes; m2c corrected: unkC1 = 3 sits in the beqz
 * delay slot so it is unconditional (m2c had this right), the
 * 31B14 jal has a nop delay slot with a0 still holding obj so it
 * is 31B14(arg0) by pass-through (m2c showed no args), and the
 * sw v0,0x1C(s0) store is real here (unlike func_8012F5F4 where
 * the 0x10 is dead); NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): always sets byte
 * unkC1 = 3; when word unkB4 & 4 calls 31B14(obj), stores word
 * unk1C = 0x10 and zeroes u16 unk98. Ends with 31CA8(obj, 6). */

struct obj_8012F75C {
    u8 pad[0x1C];
    s32 unk1C;
    u8 pad2[0x98 - 0x20];
    u16 unk98;
    u8 pad3[0xB4 - 0x9A];
    s32 unkB4;
    u8 pad4[0xC1 - 0xB8];
    u8 unkC1;
};

extern void func_80131B14(void *arg0);
extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012F75C(struct obj_8012F75C *arg0) {
    arg0->unkC1 = 3;
    if (arg0->unkB4 & 4) {
        func_80131B14(arg0);
        arg0->unk1C = 0x10;
        arg0->unk98 = 0;
    }
    func_80131CA8(arg0, 6);
}

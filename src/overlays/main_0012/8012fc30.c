/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012FC30 (main_0012.s), decoded manually from
 * raw asm (NOT verified against retail; C89-gated only,
 * promotion requires an oracle MATCH): unconditionally sets byte
 * unkC1 = 0xA (sb in the beqz delay slot). When word unkB4 &
 * 0x400: calls 31B14(obj) (a0 set in the jal delay slot),
 * zeroes byte unkC2, calls B23C(obj) (unk98 = 0 in its jal delay
 * slot), calls 31A34(obj, 8), then 8002D4C8(0xA74, 0). Ends with
 * CA8(obj, 0x1A). */

struct obj_8012FC30 {
    u8 pad[0x98];
    u16 unk98;
    u8 pad2[0xB4 - 0x9A];
    s32 unkB4;
    u8 pad3[0xC1 - 0xB8];
    u8 unkC1;
    u8 unkC2;
};

extern void func_80131B14(void *arg0);
extern void func_8012B23C(void *arg0);
extern s32 func_80131A34(void *arg0, s32 arg1);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012FC30(struct obj_8012FC30 *arg0) {
    arg0->unkC1 = 0xA;
    if (arg0->unkB4 & 0x400) {
        func_80131B14(arg0);
        arg0->unkC2 = 0;
        arg0->unk98 = 0;
        func_8012B23C(arg0);
        func_80131A34(arg0, 8);
        func_8002D4C8(0xA74, 0);
    }
    func_80131CA8(arg0, 0x1A);
}

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012A828 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Widths grounded from raw asm (sw/sw/sw/sh at 0x90/0x94/0x9C/0x9A, andi+sh at 0x72). Identical body to func_8012A8B0. */

struct obj_8012A828 {
    u8 pad[0x72];
    u16 unk72;
    u8 pad2[0x1C];
    s32 unk90;
    s32 unk94;
    s16 unk98;
    s16 unk9A;
    s32 unk9C;
};

void func_8012AAAC(void);

void func_8012A828(struct obj_8012A828 *arg0, s32 arg1) {
    arg0->unk90 = arg1;
    arg0->unk94 = 0;
    arg0->unk9C = 0;
    arg0->unk9A = 0;
    arg0->unk72 &= 0xF9FF;;
    func_8012AAAC();
}


/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80160BB4 (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shapes: arg0->unk44/unk234/unk238 and arg0->unk20->unk10.
 * The disassembly moves the outer three as words (lw/sw +0x44, sw
 * $zero +0x234/+0x238) and the inner one as a HALFWORD (sh +0x10
 * through the +0x20 pointer), so the inner member is u16 — a word
 * member would emit sw and mismatch. 0xFE9 fits the halfword.
 * func_80146CA0 was missing from the draft's declarations and is
 * added per the repo pipeline convention. Body is m2c's verbatim. */

struct inner_80160BB4 {
    u8 pad[0x10];
    u16 unk10;
};

struct data_80160BB4 {
    u8 pad[0x20];
    struct inner_80160BB4 *unk20;
    u8 pad2[0x20];
    s32 unk44;
    u8 pad3[0x1EC];
    s32 unk234;
    s32 unk238;
};

void func_80154150(void *, s32);
void func_80154A74(void *, s32);
void func_801553A8();
void func_80155440(void *);
void func_80146CA0();

void func_80160BB4(struct data_80160BB4 *arg0) {
    arg0->unk44 = (s32) (arg0->unk44 | 0x80);
    func_801553A8();
    func_80155440(arg0);
    func_80154150(arg0, 0x26);
    func_80154A74(arg0, 0x1E);
    arg0->unk234 = 0;
    arg0->unk20->unk10 = 0xFE9;
    arg0->unk238 = 0;
    func_80146CA0(arg0);
}

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012FF4C (main_0012.s), decoded manually from
 * raw asm (0x4C bytes; m2c CA8(0xF) misread corrected: a0 is
 * never written, so obj passes through (this function keeps obj
 * in a0 throughout, no frame register); NOT verified against
 * retail; C89-gated only, promotion requires an oracle MATCH):
 * unconditionally sets byte unkC1 = 5 (sb in the beqz delay
 * slot); when word unkB4 & 0x20 zeroes u16 unk5C, stores word
 * unk1C = 0x1E (real sw), zeroes u16 unk98 and target halfword
 * +0x10. Ends with CA8(obj, 0xF). */

struct obj_8012FF4C {
    u8 pad[0x1C];
    s32 unk1C;
    void *unk20;
    u8 pad2[0x5C - 0x24];
    u16 unk5C;
    u8 pad3[0x98 - 0x5E];
    u16 unk98;
    u8 pad4[0xB4 - 0x9A];
    s32 unkB4;
    u8 pad5[0xC1 - 0xB8];
    u8 unkC1;
};

struct tgt_8012FF4C {
    u8 pad[0x10];
    u16 unk10;
};

extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012FF4C(struct obj_8012FF4C *arg0) {
    arg0->unkC1 = 5;
    if (arg0->unkB4 & 0x20) {
        arg0->unk5C = 0;
        arg0->unk1C = 0x1E;
        arg0->unk98 = 0;
        ((struct tgt_8012FF4C *) arg0->unk20)->unk10 = 0;
    }
    func_80131CA8(arg0, 0xF);
}

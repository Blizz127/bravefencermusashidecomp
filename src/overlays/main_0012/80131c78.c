/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80131C78 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): v0 = arg0->unk20;
 * arg0->unkC1 = 0; *(u16 *)(v0 + 0x10) = 0; arg0->unk5E = 0 (jal
 * delay slot, lands before the call); func_80131CA8(arg0, 0xE)
 * (result ignored). Returns void. */

struct obj_80131C78 {
    u8 pad[0x20];
    u8 *unk20;
    u8 pad2[0x5E - 0x24];
    u16 unk5E;
    u8 pad3[0xC1 - 0x60];
    u8 unkC1;
};

extern s32 func_80131CA8(void *arg0, s32 arg1);

void func_80131C78(struct obj_80131C78 *arg0) {
    u8 *v0 = arg0->unk20;

    arg0->unkC1 = 0;
    *(u16 *)(v0 + 0x10) = 0;
    arg0->unk5E = 0;
    func_80131CA8(arg0, 0xE);
}

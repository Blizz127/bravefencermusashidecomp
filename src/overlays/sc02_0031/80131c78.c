/* SC02.CD FILE_031 / ov_SC02_031 retail span [80131C78,80131CA8).
 * Offset 0x9B20 at overlay base 80128158. SHA256(span)=a63e16ce4d2fa57e0fc404bb0615fb96616230ea984551cb890e0423f4e78c7e.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80131c78.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x8C820020)
MUSASHI_NATIVE_MIPS_WORD(0x2405000E)
MUSASHI_NATIVE_MIPS_WORD(0xA08000C1)
MUSASHI_NATIVE_MIPS_WORD(0xA4400010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0xA480005E)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
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
#endif

/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012FCA4,8012FCC4).
 * Offset 0x7B4C at overlay base 80128158. SHA256(span)=57d6c47c0c7eca40fe3822e390541715abfd146e70609531e20692dd6f3f9bb7.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012fca4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x2405001B)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012FCA4 (main_0012.s), decoded manually from
 * raw asm (0x20 bytes; m2c 1-arg misread corrected: a0 is never
 * written, so the incoming a0 passes through to the call;
 * NOT verified against retail; C89-gated only, promotion
 * requires an oracle MATCH): calls 31CA8(arg0, 0x1B). */

extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012FCA4(void *arg0) {
    func_80131CA8(arg0, 0x1B);
}
#endif

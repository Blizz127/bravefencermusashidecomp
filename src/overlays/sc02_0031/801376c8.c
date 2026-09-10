/* SC02.CD FILE_031 / ov_SC02_031 retail span [801376C8,801376E8).
 * Offset 0xF570 at overlay base 80128158. SHA256(span)=a35bb8fbaf71748305c02966c811364a9d8d28f5402f554c57745e3d348dc8b8.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801376c8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04DDBA)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801376C8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void*-forwarding
 * adapter, 0x18 frame. Returns func_801376E8(a0-live, 0) (a0
 * untouched past the ra save: passthrough; a1 = 0 in the jal
 * delay slot). */

struct hw2_801376C8 {
    u16 unk0;
    u16 unk2;
};

extern void *func_801376E8(void *arg0, struct hw2_801376C8 *arg1);

void *func_801376C8(void *arg0) {
    return func_801376E8(arg0, 0);
}
#endif

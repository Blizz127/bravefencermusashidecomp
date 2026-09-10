/* SC02.CD FILE_031 / ov_SC02_031 retail span [801375EC,80137614).
 * Offset 0xF494 at overlay base 80128158. SHA256(span)=54c7412411d2c4dd1e04b71d8f4179008fdb9a2225e75eec7507c75d859e88bf.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801375ec.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00052C00)
MUSASHI_NATIVE_MIPS_WORD(0x00052C03)
MUSASHI_NATIVE_MIPS_WORD(0x0C04DD85)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801375EC (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): dead tail-call
 * adapter, 0x18 frame. Returns func_80137614(a0, (s16)a1, 0)
 * (a0 live, a1 half-signed via sll/sra, a2 = 0 in the jal delay
 * slot). No callers in visible asm; the pointer result flows
 * straight through per the callee's model. */

struct opq_801375EC {
    u8 pad[0x1C];
    u16 h1C;
};

extern struct opq_801375EC *func_80137614(void *arg0, s32 arg1, s32 arg2);

struct opq_801375EC *func_801375EC(void *arg0, s32 arg1) {
    return func_80137614(arg0, (s16) arg1, 0);
}
#endif

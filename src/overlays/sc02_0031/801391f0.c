/* SC02.CD FILE_031 / ov_SC02_031 retail span [801391F0,80139220).
 * Offset 0x11098 at overlay base 80128158. SHA256(span)=bbc8f27ddf1bb0d4318c938a9fae8597e34fdcd7db62077d89b5597a5aa71d93.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801391f0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0xA4800012)
MUSASHI_NATIVE_MIPS_WORD(0xA4800014)
MUSASHI_NATIVE_MIPS_WORD(0x0C04E58D)
MUSASHI_NATIVE_MIPS_WORD(0xA4800016)
MUSASHI_NATIVE_MIPS_WORD(0x0C04E772)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801391F0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * 0x18 frame. h12 = 0; h14 = 0; func_80139634(a0) (the h16 =
 * 0 store rides the jal delay slot, so all three zeroes land
 * before 39634's body); func_80139DC8() (0-arg); return. Both
 * callee returns are ignored at every visible call site
 * (here and in func_80137840), so both are decl'd void
 * pending their own staging. */

struct st_801391F0 {
    u8 pad00[0x12];
    u16 h12;
    u16 h14;
    u16 h16;
};

extern void func_80139634(void *arg0);
extern void func_80139DC8(void);

void func_801391F0(struct st_801391F0 *arg0) {
    arg0->h12 = 0;
    arg0->h14 = 0;
    arg0->h16 = 0;
    func_80139634(arg0);
    func_80139DC8();
}
#endif

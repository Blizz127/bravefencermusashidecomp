/* SC02.CD FILE_031 / ov_SC02_031 retail span [80138948,8013895C).
 * Offset 0x107F0 at overlay base 80128158. SHA256(span)=fa42957481fd4c31f2408a423dfb62fbe5f8cbfb3fea7626028d6bf67c0f91ef.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80138948.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020007)
MUSASHI_NATIVE_MIPS_WORD(0xA4820004)
MUSASHI_NATIVE_MIPS_WORD(0xA080001F)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA080000D)
#else
#include "psx_types.h"

/* HAND MODEL of func_80138948 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * no frame. h04 = 7, b1F = 0, b0D = 0 (both sb's ride delay
 * slots and always execute). */

struct st_80138948 {
    u8 pad00[4];
    u16 h04;
    u8 pad06[7];
    u8 b0D;
    u8 pad0E[0x11];
    u8 b1F;
};

void func_80138948(struct st_80138948 *arg0) {
    arg0->h04 = 7;
    arg0->b1F = 0;
    arg0->b0D = 0;
}
#endif

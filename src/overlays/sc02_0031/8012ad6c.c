/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012AD6C,8012AD80).
 * Offset 0x2C14 at overlay base 80128158. SHA256(span)=e57477b0c4b76fea2c1197fc7b33bc2f7ae50a824ab17f3899da7aecd46c214f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012ad6c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x94820034)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4820034)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012AD6C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Read-modify-write at 0x34 grounded from raw asm (addiu 1, sh). */

struct obj_8012AD64 {
    u8 pad[0x34];
    s16 unk34;
};

void func_8012AD6C(struct obj_8012AD64 *arg0) {
    arg0->unk34 = arg0->unk34 + 1;
}
#endif

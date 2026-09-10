/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012E8C4,8012E8E0).
 * Offset 0x676C at overlay base 80128158. SHA256(span)=b886eac4cde9ddfcc4f1c843a4108d3e283ccffc117115e1d7e744717cd08271.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012e8c4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C820020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C430004)
MUSASHI_NATIVE_MIPS_WORD(0x3C048000)
MUSASHI_NATIVE_MIPS_WORD(0x00641826)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC430004)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012E8C4 (main_0012.s), decoded manually from
 * raw asm (0x1C bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): flips bit 31 of the
 * word at unk20 + 4 (xor with 0x80000000, sw). */

struct obj_8012E8C4 {
    u8 pad[0x20];
    void *unk20;
};

struct tgt_8012E8C4 {
    u8 pad[4];
    s32 unk4;
};

void func_8012E8C4(struct obj_8012E8C4 *arg0) {
    struct tgt_8012E8C4 *t;

    t = (struct tgt_8012E8C4 *) arg0->unk20;
    t->unk4 ^= 0x80000000;
}
#endif

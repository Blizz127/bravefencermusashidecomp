/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012E88C,8012E8A8).
 * Offset 0x6734 at overlay base 80128158. SHA256(span)=0163b589b16a2ca6a6f8cb0a5c60b94d92ae9be305d0e24a67ecbbd71492fd1e.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012e88c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C840020)
MUSASHI_NATIVE_MIPS_WORD(0x3C037FFF)
MUSASHI_NATIVE_MIPS_WORD(0x8C820004)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820004)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012E88C (main_0012.s), decoded manually from
 * raw asm (0x1C bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): clears bit 31 of the
 * word at unk20 + 4 (lui/ori 0x7FFFFFFF, and, sw). */

struct obj_8012E88C {
    u8 pad[0x20];
    void *unk20;
};

struct tgt_8012E88C {
    u8 pad[4];
    s32 unk4;
};

void func_8012E88C(struct obj_8012E88C *arg0) {
    struct tgt_8012E88C *t;

    t = (struct tgt_8012E88C *) arg0->unk20;
    t->unk4 &= 0x7FFFFFFF;
}
#endif

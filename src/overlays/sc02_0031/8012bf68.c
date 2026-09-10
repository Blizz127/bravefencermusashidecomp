/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012BF68,8012BF7C).
 * Offset 0x3E10 at overlay base 80128158. SHA256(span)=ef1ce5279b4ea6318ef216db4965d725a9bc85950b66da025dc530f85d0a38c5.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012bf68.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x9482005C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30427FFF)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA482005C)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012BF68 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. lhu/sh pair grounded from raw asm (u16 bit clear). */

struct obj_8012BF68 {
    u8 pad[0x5C];
    u16 unk5C;
};

void func_8012BF68(struct obj_8012BF68 *arg0) {
    arg0->unk5C &= 0x7FFF;
}
#endif

/* SC02.CD FILE_031 / ov_SC02_031 retail span [80165C58,80165C78).
 * Offset 0x3DB00 at overlay base 80128158. SHA256(span)=78e537d36c6e3d91977aefed0edd0c1263dd2825b489dd141a7842064c1bd6fd.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80165c58.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05529D)
MUSASHI_NATIVE_MIPS_WORD(0x24050011)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154A74();
void func_80165C58(void *p) {
    func_80154A74(p, 17);
}
#endif

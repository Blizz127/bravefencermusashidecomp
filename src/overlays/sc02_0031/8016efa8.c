/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016EFA8,8016EFC8).
 * Offset 0x46E50 at overlay base 80128158. SHA256(span)=d34eb8ab60f335b1fd3d6aa7730cbd6b3f40bcdc6fe697c96dd10ef1e6163a6c.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016efa8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05BBF2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_8016EFC8();                                  /* static */

void func_8016EFA8(void) {
    func_8016EFC8();
}
#endif

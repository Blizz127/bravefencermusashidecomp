/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012D38C,8012D3AC).
 * Offset 0x5234 at overlay base 80128158. SHA256(span)=68a15da95bfe9300b256e189b6bd22d19c25a47b286d1eab6a8394d5d1d239c6.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012d38c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B426)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012D38C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Raw shows a0 untouched (only a1 = 0 in the jal delay slot), so the object pointer passes through: true signature takes it. (Trailing double jr is dead padding.) */

void func_8012D098(void *arg0, s32 arg1);

void func_8012D38C(void *arg0) {
    func_8012D098(arg0, 0);
}
#endif

/* Overlay range [801619A4,801619D0) from MAIN.CD member 0012.
 * SHA256(span)=6555e7c26f2be1e10876539ab4d55d9c63c6dd500735d6ab0d18a2b6328ff24b.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x848201C8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x90428EC0)
MUSASHI_NATIVE_MIPS_WORD(0x08058672)
MUSASHI_NATIVE_MIPS_WORD(0x3042007F)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern u8 D_80078EC0;

s32 func_801619A4(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x1C8) != 0) {
        return D_80078EC0 & 0x7F;
    }
    return 0;
}
#endif

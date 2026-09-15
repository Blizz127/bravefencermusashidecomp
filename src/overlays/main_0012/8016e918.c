/* Overlay range [8016E918,8016E95C) from MAIN.CD member 0012.
 * SHA256(span)=b7190236e10ad418865c4bf2542c3990948d61aa9fbd9d490d556934785be7a5.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00A03821)
MUSASHI_NATIVE_MIPS_WORD(0x00052C00)
MUSASHI_NATIVE_MIPS_WORD(0x00052C03)
MUSASHI_NATIVE_MIPS_WORD(0x28A5000A)
MUSASHI_NATIVE_MIPS_WORD(0x10A0000A)
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x00041400)
MUSASHI_NATIVE_MIPS_WORD(0x000212C3)
MUSASHI_NATIVE_MIPS_WORD(0x3C038011)
MUSASHI_NATIVE_MIPS_WORD(0x24635218)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x24C30001)
MUSASHI_NATIVE_MIPS_WORD(0xA0430000)
MUSASHI_NATIVE_MIPS_WORD(0xA0470003)
MUSASHI_NATIVE_MIPS_WORD(0xA0400001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_80115218;

void func_8016E918(s32 arg0, s16 arg1) {
    void *temp_v0;

    if (arg1 < 0xA) {
        temp_v0 = ((s32) (arg0 << 0x10) >> 0xB) + &D_80115218;
        M2C_FIELD(temp_v0, s8 *, 0) = (s8) (arg0 + 1);
        M2C_FIELD(temp_v0, s8 *, 3) = (s8) arg1;
        M2C_FIELD(temp_v0, s8 *, 1) = 0;
    }
}
#endif

/* Overlay range [80131AC8,80131B14) from MAIN.CD member 0012.
 * SHA256(span)=9a02b0139d62b758bcb5954beadfe0b355a740e07ce4ee012330f26116be131f.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x8C8400BC)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C73D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3050FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x16000003)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0804C6C0)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00B532)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x02001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8002D4C8(s32, s32);                /* extern */
s32 func_80131CF4(s32);                             /* static */

s32 func_80131AC8(void *arg0) {
    s32 temp_s0;

    temp_s0 = func_80131CF4(M2C_FIELD(arg0, s32 *, 0xBC)) & 0xFFFF;
    if (temp_s0 == 0) {
        return 0;
    }
    func_8002D4C8(temp_s0, 0);
    return temp_s0;
}
#endif

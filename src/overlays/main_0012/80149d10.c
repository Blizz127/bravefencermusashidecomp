/* Overlay range [80149D10,80149D9C) from MAIN.CD member 0012.
 * SHA256(span)=3a3e1884c88b5fef65d770085ff326fbac06fbafa935280f0a52a25bc8d92ad9.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x8C820044)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420400)
MUSASHI_NATIVE_MIPS_WORD(0x14400019)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x3C038008)
MUSASHI_NATIVE_MIPS_WORD(0x90638EBF)
MUSASHI_NATIVE_MIPS_WORD(0x24020080)
MUSASHI_NATIVE_MIPS_WORD(0x14620014)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x90428EC0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3042007F)
MUSASHI_NATIVE_MIPS_WORD(0x1040000E)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x948200AC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420010)
MUSASHI_NATIVE_MIPS_WORD(0x10400008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C052D6E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x304300FF)
MUSASHI_NATIVE_MIPS_WORD(0x10600004)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x08052763)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
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

s32 func_8014B5B8();                                /* static */
extern u8 D_80078EBF;
extern u8 D_80078EC0;

s32 func_80149D10(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (!(M2C_FIELD(arg0, s32 *, 0x44) & 0x400)) {
        var_v0 = 0;
        if (D_80078EBF == 0x80) {
            var_v0 = 0;
            if (D_80078EC0 & 0x7F) {
                if (M2C_FIELD(arg0, u16 *, 0xAC) & 0x10) {
                    var_v0 = 1;
                    if (func_8014B5B8() & 0xFF) {
                        return 2;
                    }
                    /* Duplicate return node #7. Try simplifying control flow for better match */
                    return var_v0;
                }
                var_v0 = 0;
                /* Duplicate return node #7. Try simplifying control flow for better match */
                return var_v0;
            }
        }
    }
    return var_v0;
}
#endif

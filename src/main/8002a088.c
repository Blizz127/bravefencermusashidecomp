/* Main-exec range [8002A088,8002A108) from the SLUS executable.
 * SHA256(span)=ef1b886e1f6a8d4a27cff15c2805260a7fc03f7b484230e3aa6dd8174fdf5e13.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A842)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400017)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A89B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021900)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00021100)
MUSASHI_NATIVE_MIPS_WORD(0x3C018006)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0x942538FA)
MUSASHI_NATIVE_MIPS_WORD(0x3C018006)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x942238FA)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x00A22823)
MUSASHI_NATIVE_MIPS_WORD(0x00052C00)
MUSASHI_NATIVE_MIPS_WORD(0x0C05BA46)
MUSASHI_NATIVE_MIPS_WORD(0x00052C03)
MUSASHI_NATIVE_MIPS_WORD(0x24040B2C)
MUSASHI_NATIVE_MIPS_WORD(0x0C00B532)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x0C00AAAB)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8016E918(s32, s16);                            /* extern */
extern s32 D_800638FA;
s32 func_8002A108();                                /* static */
s32 func_8002A26C();                                /* static */
void func_8002AAAC();                                  /* static */
void func_8002D4C8(s32, s32);                              /* static */

s32 func_8002A088(void) {
    s32 temp_v0;
    s32 var_v0;

    var_v0 = 0;
    if (func_8002A108() != 0) {
        temp_v0 = func_8002A26C();
        func_8016E918(0, (s16) (*(D_800638FA + (temp_v0 * 0x10)) - *(D_800638FA + ((temp_v0 - 1) * 0x10))));
        func_8002D4C8(0xB2C, 0);
        func_8002AAAC();
        var_v0 = 1;
    }
    return var_v0;
}
#endif

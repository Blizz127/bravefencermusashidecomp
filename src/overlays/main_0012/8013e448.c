/* Overlay range [8013E448,8013E4B4) from MAIN.CD member 0012.
 * SHA256(span)=1193c59ba8ee87e59021411805b9a964f6877c60e2fa21ba9409d1e7cb27052f.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8C4274D0)
MUSASHI_NATIVE_MIPS_WORD(0x00802821)
MUSASHI_NATIVE_MIPS_WORD(0x14400010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C048012)
MUSASHI_NATIVE_MIPS_WORD(0x24846CAC)
MUSASHI_NATIVE_MIPS_WORD(0x0C004CAF)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00402021)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x8C6374D8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0064182A)
MUSASHI_NATIVE_MIPS_WORD(0x10600007)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8C4274DC)
MUSASHI_NATIVE_MIPS_WORD(0x0804F929)
MUSASHI_NATIVE_MIPS_WORD(0x0082102A)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00A02021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_800132BC(void *, s32);                        /* extern */
extern s32 *D_80126CAC;
extern s32 (*D_801274D0)(s32, s32);
extern s32 D_801274D8;
extern s32 D_801274DC;

s32 func_8013E448(s32 arg0) {
    s32 temp_v0;
    s32 var_v0;

    if (D_801274D0 == 0) {
        temp_v0 = func_800132BC(&D_80126CAC, arg0);
        var_v0 = 0;
        if (D_801274D8 < temp_v0) {
            return temp_v0 < D_801274DC;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_v0;
    }
    var_v0 = D_801274D0(arg0, arg0);
    return var_v0;
}
#endif

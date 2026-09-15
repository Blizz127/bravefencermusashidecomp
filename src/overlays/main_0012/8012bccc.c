/* Overlay range [8012BCCC,8012BD14) from MAIN.CD member 0012.
 * SHA256(span)=2ca7fbe997408ebb079cd175d8e5b9098b2913168c8f75fb283602daccdadf04.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x84426CBA)
MUSASHI_NATIVE_MIPS_WORD(0x3C058012)
MUSASHI_NATIVE_MIPS_WORD(0x24A56B58)
MUSASHI_NATIVE_MIPS_WORD(0x14400006)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x24840004)
MUSASHI_NATIVE_MIPS_WORD(0x0C004D1E)
MUSASHI_NATIVE_MIPS_WORD(0x24A5015C)
MUSASHI_NATIVE_MIPS_WORD(0x0804AF41)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C027FFF)
MUSASHI_NATIVE_MIPS_WORD(0x3442FFFF)
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

s32 func_80013478(s32, void *);                     /* extern */
extern s32 *D_80126B58;
extern s16 D_80126CBA;

s32 func_8012BCCC(s32 arg0) {
    if (D_80126CBA == 0) {
        return func_80013478(arg0 + 4, &D_80126B58 + 0x15C);
    }
    return 0x7FFFFFFF;
}
#endif

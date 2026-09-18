/* Overlay range [8012BCCC,8012BD14) from MAIN.CD member 0012.
 * SHA256(span)=2ca7fbe997408ebb079cd175d8e5b9098b2913168c8f75fb283602daccdadf04.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
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
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8012BCCC - 18 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_80013478(s32 a0, s32 a1);
extern s16 D_80126CBA;
extern s32 D_80126B58;

s32 func_8012BCCC(s32 a0) {
    s32 *p = &D_80126B58;
    if (D_80126CBA != 0) {
        return 0x7FFFFFFF;
    }
    return func_80013478(a0 + 4, (s32)p + 0x15C);
}
#endif

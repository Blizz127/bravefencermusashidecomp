/* Overlay range [80130088,801300F4) from MAIN.CD member 0012.
 * SHA256(span)=a8c2d8590c6ff08df34ddae94130e50a5368c734aaa46f06406f7ed012930430.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C04AF33)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x34038FFF)
MUSASHI_NATIVE_MIPS_WORD(0x0062182A)
MUSASHI_NATIVE_MIPS_WORD(0x14600007)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C6B2)
MUSASHI_NATIVE_MIPS_WORD(0x24050032)
MUSASHI_NATIVE_MIPS_WORD(0x1440000A)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0804C036)
MUSASHI_NATIVE_MIPS_WORD(0x24050033)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C6B2)
MUSASHI_NATIVE_MIPS_WORD(0x24050033)
MUSASHI_NATIVE_MIPS_WORD(0x14400004)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x24050032)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C6B2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80130088 - 27 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_8012BCCC(s32 a0);
extern s32 func_80131AC8(void *a0);

void func_80130088(void *a0) {
    s32 v0 = func_8012BCCC((s32)a0);
    if (v0 <= 0x8FFF) {
        if (((s32 (*)(void *, s32))func_80131AC8)(a0, 0x32)) {
            return;
        }
        ((s32 (*)(void *, s32))func_80131AC8)(a0, 0x33);
    } else {
        if (((s32 (*)(void *, s32))func_80131AC8)(a0, 0x33)) {
            return;
        }
        ((s32 (*)(void *, s32))func_80131AC8)(a0, 0x32);
    }
}
#endif

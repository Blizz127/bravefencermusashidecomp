/* Overlay range [8012C51C,8012C588) from MAIN.CD member 0012.
 * SHA256(span)=edde7c6eacd220c84cc5a4f4dbac6f9015f0976aeb1fef6a3499442be260046f.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x00A03021)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x24636720)
MUSASHI_NATIVE_MIPS_WORD(0x14C00003)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0804B150)
MUSASHI_NATIVE_MIPS_WORD(0x24659B80)
MUSASHI_NATIVE_MIPS_WORD(0x24C5010C)
MUSASHI_NATIVE_MIPS_WORD(0x10A30008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x94A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24A5010C)
MUSASHI_NATIVE_MIPS_WORD(0x14A3FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x10A00003)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B224)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8012C51C - 27 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u8 D_80126720[];
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);

s32 func_8012C51C(void *a0, s32 a1) {
    u8 *base = D_80126720;
    u8 *p;
    s32 ret;
    if (a1 == 0) {
        p = base - 0x6480;
    } else {
        p = (u8 *)(a1 + 0x10C);
    }
    if (p != base) {
        do {
            if (*(u16 *)p == 0) goto found;
            p += 0x10C;
        } while (p != base);
    }
    p = 0;
found:
    ret = 0;
    if (p != 0) {
        ret = func_8012C890((s32)a0, (s32)p, a1);
    }
    return ret;
}
#endif

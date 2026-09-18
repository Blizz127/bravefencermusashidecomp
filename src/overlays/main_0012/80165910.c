/* Overlay range [80165910,80165938) from MAIN.CD member 0012.
 * SHA256(span)=ce9caf6bdfe1181dcfdfec6b154df40f72a0236f4db91091622c23f171f9040e.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x90428EC4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400004)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xA0228EC4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00601021)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80165910 - 10 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s8 D_80078EC4;

s32 func_80165910(void)
{
    s32 v;
    s32 ret;
    v = (u8)D_80078EC4;
    ret = v;
    if (v == 0) {
        register s32 one __asm__("$2");
        one = 1;
        __asm__ __volatile__("" : "=r"(one) : "0"(one));
        D_80078EC4 = one;
    }
    return ret;
}
#endif

/* Overlay range [801535F4,8015369C) from MAIN.CD member 0012.
 * SHA256(span)=0f7e933ce2ceec1517da91fa5ebe70770e061f08cc12223a7beb27a5812d2e29.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x0C053B4A)
MUSASHI_NATIVE_MIPS_WORD(0x00008821)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B64)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8E020034)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x18400006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C05330A)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24110001)
MUSASHI_NATIVE_MIPS_WORD(0x0C053E81)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x00402021)
MUSASHI_NATIVE_MIPS_WORD(0x30824000)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00801821)
MUSASHI_NATIVE_MIPS_WORD(0x08054DA1)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x30822000)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x30638000)
MUSASHI_NATIVE_MIPS_WORD(0x08054DA1)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x14600002)
MUSASHI_NATIVE_MIPS_WORD(0x24020004)
MUSASHI_NATIVE_MIPS_WORD(0x02201021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801535F4 - 42 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_8014ED28();
extern void func_80146D90(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014FA04(s32 a0);

s32 func_801535F4(void *arg0) {
    s32 var_s1;
    register u32 flags __asm__("$4");
    register u32 fcopy __asm__("$3");
    s32 ret;
    var_s1 = 0;
    if (((s32 (*)(void))func_8014ED28)() != 0) {
        func_80146D90((s32)arg0);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x34) > 0) &&
        (((s32 (*)(s32))func_8014CC28)((s32)arg0) != 0)) {
        var_s1 = 1;
    }
    flags = ((s32 (*)(s32))func_8014FA04)((s32)arg0);
    fcopy = flags;
    if (flags & 0x4000) {
        ret = 2;
    } else if (flags & 0x2000) {
        ret = 1;
    } else {
        ret = 4;
        if ((fcopy & 0x8000) == 0) {
            ret = var_s1;
        }
    }
    __asm__ __volatile__("" : : "r"(flags));
    return ret;
}
#endif

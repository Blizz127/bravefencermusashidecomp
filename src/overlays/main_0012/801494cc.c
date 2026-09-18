/* Overlay range [801494CC,80149544) from MAIN.CD member 0012.
 * SHA256(span)=ebe943cd289f70892de886918c5a0be347976fc7104f9817b81a42630f66867b.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0024)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00020)
MUSASHI_NATIVE_MIPS_WORD(0x94A20002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20018)
MUSASHI_NATIVE_MIPS_WORD(0x94A20006)
MUSASHI_NATIVE_MIPS_WORD(0x00C08021)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001A)
MUSASHI_NATIVE_MIPS_WORD(0x94A2000A)
MUSASHI_NATIVE_MIPS_WORD(0x27A60010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001C)
MUSASHI_NATIVE_MIPS_WORD(0x8C840020)
MUSASHI_NATIVE_MIPS_WORD(0x27A50018)
MUSASHI_NATIVE_MIPS_WORD(0x0C04BC0E)
MUSASHI_NATIVE_MIPS_WORD(0x24840034)
MUSASHI_NATIVE_MIPS_WORD(0x97A20010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA6020002)
MUSASHI_NATIVE_MIPS_WORD(0x97A20012)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA6020006)
MUSASHI_NATIVE_MIPS_WORD(0x97A20014)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA602000A)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801494CC - 30 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_8012F038(int param_1, short *param_2, short *param_3);

void func_801494CC(s32 a0, u16 *a1, u16 *a2) {
    u16 dst[3];
    u16 src[3];
    src[0] = a1[1];
    src[1] = a1[3];
    src[2] = a1[5];
    ((void (*)(s32, u16 *, u16 *))func_8012F038)(*(s32 *)(a0 + 0x20) + 0x34, src, dst);
    a2[1] = dst[0];
    a2[3] = dst[1];
    a2[5] = dst[2];
}
#endif

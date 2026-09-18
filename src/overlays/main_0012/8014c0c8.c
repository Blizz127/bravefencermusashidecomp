/* Overlay range [8014C0C8,8014C118) from MAIN.CD member 0012.
 * SHA256(span)=cfa5704061d05f5ef6a8afb98ec93c71cb1dcc23bbdd6756e3e1824bed81cef4.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x00063400)
MUSASHI_NATIVE_MIPS_WORD(0x00063403)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x246302A0)
MUSASHI_NATIVE_MIPS_WORD(0x94620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14450005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x846200FC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10460006)
MUSASHI_NATIVE_MIPS_WORD(0x00601021)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x2C820060)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF5)
MUSASHI_NATIVE_MIPS_WORD(0x2463010C)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8014C0C8 - 20 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u8 D_801202A0[];

s32 func_8014C0C8(s32 a0_unused, s32 a1, s32 a2) {
    s32 i = 0;
    s32 key = (s16)a2;
    u8 *p = D_801202A0;
    do {
        if (*(u16 *)(p + 0x0) == a1) {
            if (*(s16 *)(p + 0xFC) == key) {
                return (s32)p;
            }
        }
        i += 1;
        p += 0x10C;
    } while ((u32)i < 0x60);
    return 0;
}
#endif

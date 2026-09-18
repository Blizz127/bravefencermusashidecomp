/* Overlay range [8012B030,8012B0B4) from MAIN.CD member 0012.
 * SHA256(span)=3a4109139862d1baba52ae36d213735dc95126239691f0e50142e2fcb4c0a5dc.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00018)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x96020006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x9602000A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20012)
MUSASHI_NATIVE_MIPS_WORD(0x9602000E)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04D144)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20014)
MUSASHI_NATIVE_MIPS_WORD(0x1040000D)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x97A20010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA6020006)
MUSASHI_NATIVE_MIPS_WORD(0x97A20012)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA602000A)
MUSASHI_NATIVE_MIPS_WORD(0x97A30014)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xA600000C)
MUSASHI_NATIVE_MIPS_WORD(0xA6000008)
MUSASHI_NATIVE_MIPS_WORD(0xA6000004)
MUSASHI_NATIVE_MIPS_WORD(0xA603000E)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8012B030 - 33 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_80134510(s32 arg);

s32 func_8012B030(u8 *a0) {
    u16 local[3];
    local[0] = *(u16 *)(a0 + 0x6);
    local[1] = *(u16 *)(a0 + 0xA);
    local[2] = *(u16 *)(a0 + 0xE);
    if (func_80134510((s32)local) == 0) {
        return 0;
    }
    *(u16 *)(a0 + 0x6) = local[0];
    *(u16 *)(a0 + 0xA) = local[1];
    *(u16 *)(a0 + 0xE) = local[2];
    *(u16 *)(a0 + 0xC) = 0;
    *(u16 *)(a0 + 0x8) = 0;
    *(u16 *)(a0 + 0x4) = 0;
    return 1;
}
#endif

/* Overlay range [80147118,80147264) from MAIN.CD member 0012.
 * SHA256(span)=d988622db65ecd73bc19f45f0d688f9fb1a4dc223c8505753b32d32b8bee3d26.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x84830060)
MUSASHI_NATIVE_MIPS_WORD(0x84820068)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00620018)
MUSASHI_NATIVE_MIPS_WORD(0x00001812)
MUSASHI_NATIVE_MIPS_WORD(0x04610002)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80147118 - 83 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


void func_80147118(s32 a0) {
    s32 vec[3];
    vec[0] = ((s32)(*(s16 *)(a0 + 0x60) * *(s16 *)(a0 + 0x68)) / 4096);
    vec[0] = ((s32)(vec[0] * *(s16 *)(a0 + 0x70)) / 4096);
    vec[1] = ((s32)(*(s16 *)(a0 + 0x62) * *(s16 *)(a0 + 0x6A)) / 4096);
    vec[1] = ((s32)(vec[1] * *(s16 *)(a0 + 0x72)) / 4096);
    vec[2] = ((s32)(*(s16 *)(a0 + 0x64) * *(s16 *)(a0 + 0x6C)) / 4096);
    vec[2] = ((s32)(vec[2] * *(s16 *)(a0 + 0x74)) / 4096);
    if (0xFFFF < vec[0]) {
        vec[0] = 0xFFFF;
    }
    if (0xFFFF < vec[1]) {
        vec[1] = 0xFFFF;
    }
    if (0xFFFF < vec[2]) {
        vec[2] = 0xFFFF;
    }
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = vec[0];
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = vec[1];
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = vec[2];
}
#endif

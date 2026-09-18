/* Overlay range [8016F95C,8016F9C4) from MAIN.CD member 0012.
 * SHA256(span)=8f0f906a1a18698ef403450d62c1b7857813e1e4bbcaa5785d228aec6acd066c.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C058012)
MUSASHI_NATIVE_MIPS_WORD(0x24A5F73E)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x94A60000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14C00005)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C731)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x0805BE68)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C747)
MUSASHI_NATIVE_MIPS_WORD(0x30C600FF)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C64A)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8016F95C - 26 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern void func_80171928(void *a0);
extern u16 D_8011F73E;

void func_8016F95C(void *a0) {
    u16 *p = &D_8011F73E;
    u16 v = *p;
    s32 r;
    if (v == 0) {
        r = func_80171CC4(a0, p - 3);
    } else {
        r = func_80171D1C(a0, p - 3, v & 0xFF);
    }
    if (r != 0) {
        func_80171928(a0);
    }
}
#endif

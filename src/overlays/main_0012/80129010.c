/* Overlay range [80129010,801290DC) from MAIN.CD member 0012.
 * SHA256(span)=81920458822b3684d851d5b298d56ae2a8106df0c4f426b2261ad9fcc461d7f2.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8442DB2C)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80129010 - 51 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s16 D_8011DB2C;
extern s16 D_8011DB30;
extern s32 D_80126AEC;

void func_80129010(void) {
    s32 i;
    s32 s1;
    s32 idx;
    void (*fp)(s32);
    s1 = (s32)&D_8011DB30;
    if (D_8011DB2C == 0) {
        return;
    }
    i = 0;
    do {
        idx = *(u16 *)s1;
        if (idx != 0) {
            fp = (void (*)(s32))(*(s32 *)((idx << 2) + (*(s32 *)&D_80126AEC)));
            fp(s1);
            if (*(s32 *)(s1 + 0x20) != 0) {
                *(s16 *)(*(s32 *)(s1 + 0x20) + 0x8) = *(u16 *)(s1 + 0x6);
                *(s16 *)(*(s32 *)(s1 + 0x20) + 0xA) = *(u16 *)(s1 + 0xA);
                *(s16 *)(*(s32 *)(s1 + 0x20) + 0xC) = *(u16 *)(s1 + 0xE);
            }
        }
        i++;
        s1 += 0x38;
    } while (i < 0x80);
}
#endif

/* Overlay range [8013895C,80138AB4) from MAIN.CD member 0012.
 * SHA256(span)=846c8c8be63514dd260a88be084b9265b482bdfacf64ebb8cefd9d991a2dce5b.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8C427524)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8013895C - 86 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 D_80127524;
extern s16 func_80138DB8(s32 a0, u8 a1, s32 a2);
extern void func_80138B88(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8013895C(s32 a0) {
    if ((s32)D_80127524 == a0 || (*(s32 *)(a0 + 8) & 0x2000)) {
        if ((s16)func_80138DB8(a0, 0, 0x40)) {
            *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x1F) + 1;
            func_80138B88(a0);
            func_8002D4C8(0x630, 0);
        } else if ((s16)func_80138DB8(a0, 0, 0x1000)) {
            *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x1F) - 1;
            if ((s8)*(s8 *)(a0 + 0x1F) < 0) {
                *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x21) - 1;
            }
            func_8002D4C8(0x62F, 0);
        } else if ((s16)func_80138DB8(a0, 0, 0x4000)) {
            u8 cur = *(u8 *)(a0 + 0x1F);
            u8 lim = *(u8 *)(a0 + 0x21);
            *(s8 *)(a0 + 0x1F) = cur + 1;
            if (!((s32)(s8)(*(s8 *)(a0 + 0x1F)) < (s32)lim)) {
                *(s8 *)(a0 + 0x1F) = 0;
            }
            func_8002D4C8(0x62F, 0);
        } else if (*(s32 *)(a0 + 8) & 0x2) {
            if ((s16)func_80138DB8(a0, 0, 0x30)) {
                *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x21) - 1;
                func_8002D4C8(0x62F, 0);
            }
        }
    }
}
#endif

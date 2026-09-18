/* Overlay range [80138DE0,80138ED0) from MAIN.CD member 0012.
 * SHA256(span)=15677e92abe0e8c1cc8cf2f72e1d869999df25a69f85ad6913530e9fe9cee8f1.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8C427548)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80138DE0 - 60 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_80138ED0(u8 *param_1, u32 param_2, u8 *param_3);

s32 func_80138DE0(u8 *arg0, u8 arg1, s32 arg2) {
    extern s32 D_80127548[];
    extern u8 D_800D3AB4[];
    u16 *p;
    if (D_80127548[0] == 0) {
        return 0;
    }
    p = (u16 *)(arg0 + 0x44);
    if ((*(u32 *)(arg0 + 8) & 0x400) == 0) {
        p = (u16 *)(arg0 + 0x10);
        if (*(s16 *)(arg0 + 4) == 8) {
            p = (u16 *)(arg0 + 0x44);
        }
    }
    if (arg1 >= 0xE0) {
        arg2 = func_80138ED0(arg0, 0x1F, D_800D3AB4);
        if (arg2 != 0) {
            return 0;
        }
        *p = *p + 2;
    } else if (arg1 >= 0x20) {
        arg2 = func_80138ED0(arg0, (u16)(arg1 - 0x20), D_800D3AB4);
        if (arg2 != 0) {
            return 0;
        }
        *p = *p + 1;
    }
    if (arg2 != 0) {
        return 0;
    }
    D_80127548[0] = D_80127548[0] - 1;
    return D_80127548[0];
}
#endif

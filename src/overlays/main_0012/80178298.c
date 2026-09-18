/* Overlay range [80178298,801783D0) from MAIN.CD member 0012.
 * SHA256(span)=877e1f8f1fc80ad2f24d89d606edc8d64e55129f8ba2fcd01675a091464bd149.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2C420080)
MUSASHI_NATIVE_MIPS_WORD(0x10400048)
MUSASHI_NATIVE_MIPS_WORD(0x00804821)
MUSASHI_NATIVE_MIPS_WORD(0x240A0008)
MUSASHI_NATIVE_MIPS_WORD(0x24880012)
MUSASHI_NATIVE_MIPS_WORD(0x84A30000)
MUSASHI_NATIVE_MIPS_WORD(0x24023870)
MUSASHI_NATIVE_MIPS_WORD(0x10620015)
MUSASHI_NATIVE_MIPS_WORD(0x28623871)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x24021850)
MUSASHI_NATIVE_MIPS_WORD(0x1062000C)
MUSASHI_NATIVE_MIPS_WORD(0x24021858)
MUSASHI_NATIVE_MIPS_WORD(0x1062000B)
MUSASHI_NATIVE_MIPS_WORD(0x24C20004)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0CE)
MUSASHI_NATIVE_MIPS_WORD(0xA506FFF6)
MUSASHI_NATIVE_MIPS_WORD(0x24023871)
MUSASHI_NATIVE_MIPS_WORD(0x1062000D)
MUSASHI_NATIVE_MIPS_WORD(0x24023872)
MUSASHI_NATIVE_MIPS_WORD(0x1062000E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0CE)
MUSASHI_NATIVE_MIPS_WORD(0xA506FFF6)
MUSASHI_NATIVE_MIPS_WORD(0x24C20004)
MUSASHI_NATIVE_MIPS_WORD(0xA502FFF6)
MUSASHI_NATIVE_MIPS_WORD(0x24E2FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0D7)
MUSASHI_NATIVE_MIPS_WORD(0xA502FFF8)
MUSASHI_NATIVE_MIPS_WORD(0x24C60008)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0ED)
MUSASHI_NATIVE_MIPS_WORD(0x24A50002)
MUSASHI_NATIVE_MIPS_WORD(0x24C60004)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0ED)
MUSASHI_NATIVE_MIPS_WORD(0x24A50002)
MUSASHI_NATIVE_MIPS_WORD(0x24C60002)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0ED)
MUSASHI_NATIVE_MIPS_WORD(0x24A50002)
MUSASHI_NATIVE_MIPS_WORD(0xA507FFF8)
MUSASHI_NATIVE_MIPS_WORD(0x84A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28420861)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0D7)
MUSASHI_NATIVE_MIPS_WORD(0x24C60008)
MUSASHI_NATIVE_MIPS_WORD(0x24C60007)
MUSASHI_NATIVE_MIPS_WORD(0x3C0300FF)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C046480)
MUSASHI_NATIVE_MIPS_WORD(0x34848080)
MUSASHI_NATIVE_MIPS_WORD(0x2522FFEC)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x3C030400)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0xAD220000)
MUSASHI_NATIVE_MIPS_WORD(0xAD04FFF2)
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x25290014)
MUSASHI_NATIVE_MIPS_WORD(0xA102FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x90A30000)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x24024056)
MUSASHI_NATIVE_MIPS_WORD(0xA502FFFC)
MUSASHI_NATIVE_MIPS_WORD(0xA50AFFFE)
MUSASHI_NATIVE_MIPS_WORD(0xA50A0000)
MUSASHI_NATIVE_MIPS_WORD(0xA103FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x25080014)
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2C420080)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFBC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x01201021)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80178298 - 78 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


u32 *func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4) {
    u8 bVar1;
    short sVar2;
    if (*param_2 < 0x80) {
        do {
            sVar2 = *(short *)param_2;
            switch (sVar2) {
            case 0x1850:
            case 0x1858:
                *(short *)((u8 *)param_1 + 8) = param_3 + 4;
                *(short *)((u8 *)param_1 + 0xA) = param_4 + -7;
                break;
            case 0x3870:
                param_3 = param_3 + 8;
                param_2 = param_2 + 2;
                continue;
            case 0x3871:
                param_3 = param_3 + 4;
                param_2 = param_2 + 2;
                continue;
            case 0x3872:
                param_3 = param_3 + 2;
                param_2 = param_2 + 2;
                continue;
            default:
                *(short *)((u8 *)param_1 + 8) = param_3;
                *(short *)((u8 *)param_1 + 0xA) = param_4;
                if (*(short *)param_2 >= 0x861) {
                    param_3 = param_3 + 8;
                } else {
                    param_3 = param_3 + 7;
                }
                break;
            }
            *param_1 = (u32)(param_1 + -5) & 0xffffff | 0x4000000;
            *(u32 *)((u8 *)param_1 + 4) = 0x64808080;
            ((u8 *)param_1)[0xC] = *param_2;
            param_2 = param_2 + 1;
            bVar1 = *param_2;
            param_2 = param_2 + 1;
            *(short *)((u8 *)param_1 + 0xE) = 0x4056;
            ((u8 *)param_1)[0xD] = bVar1;
            *(short *)((u8 *)param_1 + 0x10) = 8;
            *(short *)((u8 *)param_1 + 0x12) = 8;
            param_1 = param_1 + 5;
        } while (*param_2 < 0x80);
    }
    return param_1;
}
#endif

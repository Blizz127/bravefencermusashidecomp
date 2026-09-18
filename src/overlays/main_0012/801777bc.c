/* Overlay range [801777BC,801778A8) from MAIN.CD member 0012.
 * SHA256(span)=0fa2e36925478fcd70f5a30475877df57f8ce80e1ec1511e0fccc63a80380e4e.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00804821)
MUSASHI_NATIVE_MIPS_WORD(0x3C0C0100)
MUSASHI_NATIVE_MIPS_WORD(0x87A20014)
MUSASHI_NATIVE_MIPS_WORD(0x87A30010)
MUSASHI_NATIVE_MIPS_WORD(0x24420100)
MUSASHI_NATIVE_MIPS_WORD(0x00021180)
MUSASHI_NATIVE_MIPS_WORD(0x34420016)
MUSASHI_NATIVE_MIPS_WORD(0x0002C400)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20018)
MUSASHI_NATIVE_MIPS_WORD(0x1860002F)
MUSASHI_NATIVE_MIPS_WORD(0x00005821)
MUSASHI_NATIVE_MIPS_WORD(0x00606821)
MUSASHI_NATIVE_MIPS_WORD(0x25AFFFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00027403)
MUSASHI_NATIVE_MIPS_WORD(0x00073C00)
MUSASHI_NATIVE_MIPS_WORD(0x2488000C)
MUSASHI_NATIVE_MIPS_WORD(0x00051400)
MUSASHI_NATIVE_MIPS_WORD(0x00021702)
MUSASHI_NATIVE_MIPS_WORD(0x14400007)
MUSASHI_NATIVE_MIPS_WORD(0x00405021)
MUSASHI_NATIVE_MIPS_WORD(0x000B1400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x104F0003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x144E0003)
MUSASHI_NATIVE_MIPS_WORD(0x3C0300FF)
MUSASHI_NATIVE_MIPS_WORD(0x00006021)
MUSASHI_NATIVE_MIPS_WORD(0x3C0300FF)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C047480)
MUSASHI_NATIVE_MIPS_WORD(0x34848080)
MUSASHI_NATIVE_MIPS_WORD(0x2522FFEC)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x3C030300)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0xAD220000)
MUSASHI_NATIVE_MIPS_WORD(0x30C2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00E21025)
MUSASHI_NATIVE_MIPS_WORD(0x004C1025)
MUSASHI_NATIVE_MIPS_WORD(0xAD02FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x000A10C0)
MUSASHI_NATIVE_MIPS_WORD(0x24420008)
MUSASHI_NATIVE_MIPS_WORD(0x34424000)
MUSASHI_NATIVE_MIPS_WORD(0x03021025)
MUSASHI_NATIVE_MIPS_WORD(0xAD04FFF8)
MUSASHI_NATIVE_MIPS_WORD(0xAD020000)
MUSASHI_NATIVE_MIPS_WORD(0x25080014)
MUSASHI_NATIVE_MIPS_WORD(0x25290014)
MUSASHI_NATIVE_MIPS_WORD(0x24C60008)
MUSASHI_NATIVE_MIPS_WORD(0x25620001)
MUSASHI_NATIVE_MIPS_WORD(0x00405821)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x004D102A)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFD9)
MUSASHI_NATIVE_MIPS_WORD(0x00052900)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x01201021)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801777BC - 59 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


void *func_801777BC(void *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6)
{
    u32 cl;
    u32 flag;
    u32 nn;
    register u32 n __asm__("$10");
    u32 t;
    register u32 col __asm__("$4");
    u32 mask;
    s32 cnt;
    s32 dp;
    s16 i;
    flag = 0x1000000;
    cl = ((((s16)a5 + 0x100) << 6) | 0x16) << 16;
    dp = a6;
    i = 0;
    if ((s16)a4 > 0) {
        cnt = (s16)a4;
        do {
            nn = ((u32)(a1 << 16)) >> 28;
            n = nn;
            if (((nn != 0) || (i == cnt - 1)) || (i == ((s32)(dp << 16) >> 16))) {
                flag = 0;
            }
            mask = 0xffffff;
            col = 0x74808080;
            t = ((u32)((u32 *)a0 - 5)) & mask;
            mask = 0x3000000;
            t = t | mask;
            ((u32 *)a0)[0] = t;
            t = ((a3 << 16) | (a2 & 0xffff)) | flag;
            ((u32 *)a0)[2] = t;
            ((u32 *)a0)[1] = col;
            t = n << 3;
            t = t + 8;
            t = t | 0x4000;
            ((u32 *)a0)[3] = cl | t;
            a0 = (void *)((u32 *)a0 + 5);
            a2 += 8;
            a1 <<= 4;
            col = 0;
            i++;
        } while ((s16)i < cnt);
    }
    return a0;
}
#endif

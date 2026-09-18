/* Overlay range [8015B6F4,8015B7B4) from MAIN.CD member 0012.
 * SHA256(span)=024cbceb7e883f1a73fd48410134cb709695aa10c32bae852440ba1ac552a1fb.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C0526AA)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x10400025)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C055992)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8E0300B4)
MUSASHI_NATIVE_MIPS_WORD(0x24020006)
MUSASHI_NATIVE_MIPS_WORD(0xA20201AA)
MUSASHI_NATIVE_MIPS_WORD(0x8E020044)
MUSASHI_NATIVE_MIPS_WORD(0x920400BC)
MUSASHI_NATIVE_MIPS_WORD(0xAE03023C)
MUSASHI_NATIVE_MIPS_WORD(0x8E0300B4)
MUSASHI_NATIVE_MIPS_WORD(0x34420002)
MUSASHI_NATIVE_MIPS_WORD(0xAE020044)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800D)
MUSASHI_NATIVE_MIPS_WORD(0x24424A9C)
MUSASHI_NATIVE_MIPS_WORD(0x14620004)
MUSASHI_NATIVE_MIPS_WORD(0xA2040244)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x08056DD8)
MUSASHI_NATIVE_MIPS_WORD(0x2405000B)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x2405000C)
MUSASHI_NATIVE_MIPS_WORD(0x0C055054)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05529D)
MUSASHI_NATIVE_MIPS_WORD(0x24050022)
MUSASHI_NATIVE_MIPS_WORD(0xA20000DA)
MUSASHI_NATIVE_MIPS_WORD(0x24040004)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x24060005)
MUSASHI_NATIVE_MIPS_WORD(0x0C051A65)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x0C051CC9)
MUSASHI_NATIVE_MIPS_WORD(0x24040400)
MUSASHI_NATIVE_MIPS_WORD(0x0C051CC0)
MUSASHI_NATIVE_MIPS_WORD(0x240405F3)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8015B6F4 - 48 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_80149AA8(s32 *a0);
extern void func_80156648(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147324(s32 arg0);
extern void func_80147300(u16 arg0);
extern s32 D_800D4A9C;

int func_8015B6F4(int param_1)
{
    register int b4 __asm__("$3");
    register unsigned int f44 __asm__("$2");
    register unsigned int bc __asm__("$4");
    if (((int (*)(void))func_80149AA8)() == 0) return 0;
    ((void (*)(int))func_80156648)(param_1);
    b4 = *(int *)(param_1 + 0xb4);
    *(unsigned char *)(param_1 + 0x1aa) = 6;
    __asm__ __volatile__("" ::: "memory");
    f44 = *(unsigned int *)(param_1 + 0x44);
    bc = *(unsigned char *)(param_1 + 0xbc);
    *(int *)(param_1 + 0x23c) = b4;
    *(unsigned int *)(param_1 + 0x44) = f44 | 2;
    *(unsigned char *)(param_1 + 0x244) = bc;
    if (*(int *)(param_1 + 0xb4) == (int)&D_800D4A9C) {
        func_80154150(param_1, 0xb);
    } else {
        func_80154150(param_1, 0xc);
    }
    func_80154A74(param_1, 0x22);
    *(unsigned char *)(param_1 + 0xda) = 0;
    ((void (*)(int, int, int, int))func_80146994)(4, param_1, 5, 0);
    func_80147324(0x400);
    ((void (*)(int))func_80147300)(0x5f3);
    return 1;
}
#endif

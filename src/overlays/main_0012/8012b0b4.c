/* Overlay range [8012B0B4,8012B14C) from MAIN.CD member 0012.
 * SHA256(span)=c09c5dbc239a729e1c5e2886118b949d331e05ac400a04bc5d26e41c1cabb228.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20018)
MUSASHI_NATIVE_MIPS_WORD(0x00809021)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x24B0FC00)
MUSASHI_NATIVE_MIPS_WORD(0x32100FFF)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00C08821)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x0C011E52)
MUSASHI_NATIVE_MIPS_WORD(0xAFB3001C)
MUSASHI_NATIVE_MIPS_WORD(0x00510018)
MUSASHI_NATIVE_MIPS_WORD(0x3C02FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x02629824)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x00003812)
MUSASHI_NATIVE_MIPS_WORD(0x00071303)
MUSASHI_NATIVE_MIPS_WORD(0x3042FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0C011E1F)
MUSASHI_NATIVE_MIPS_WORD(0x02629825)
MUSASHI_NATIVE_MIPS_WORD(0x00118823)
MUSASHI_NATIVE_MIPS_WORD(0x00510018)
MUSASHI_NATIVE_MIPS_WORD(0x3273FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x02401021)
MUSASHI_NATIVE_MIPS_WORD(0x00003812)
MUSASHI_NATIVE_MIPS_WORD(0x00071B03)
MUSASHI_NATIVE_MIPS_WORD(0x00031C00)
MUSASHI_NATIVE_MIPS_WORD(0x02639825)
MUSASHI_NATIVE_MIPS_WORD(0xAC530000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x8FB3001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8012B0B4 - 38 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern int func_80047948(int a0);
extern int func_8004787C(int a0);

void func_8012B0B4(unsigned int *param_1, int param_2, int param_3)
{
    int iVar1, iVar2;
    register int prod __asm__("$7");          /* mflo dest = $a3 (both products) */
    register unsigned int *p __asm__("$2");    /* store addr copied into $v0 */
    register int sh1 __asm__("$2");            /* shares $v0 with p (non-overlapping) */
    register int sh2 __asm__("$3");            /* 2nd-product shift -> $v1 */
    unsigned int uVar3, result;
    uVar3 = (param_2 - 0x400U) & 0xfff;
    iVar1 = func_80047948(uVar3);
    result &= 0xFFFF0000;
    prod = iVar1 * param_3;
    sh1 = prod >> 0xc;
    result |= sh1 & 0xFFFF;
    iVar2 = func_8004787C(uVar3);
    prod = iVar2 * -param_3;
    result &= 0xFFFF;
    /* Force the param_1->$v0 copy AND let the scheduler hoist it into the
       mult->mflo delay slot (a plain `p = param_1` gets coalesced away). */
    __asm__ ("addu %0,%1,$zero" : "=r"(p) : "r"(param_1));
    sh2 = prod >> 0xc;
    result |= sh2 << 0x10;
    *p = result;
}
#endif

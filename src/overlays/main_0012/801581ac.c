/* Overlay range [801581AC,8015824C) from MAIN.CD member 0012.
 * SHA256(span)=4675c3cd996cd4ca155017122b8ae87b4ff6bfba2e5b095b56b73a88010b1a2a.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00020)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x8E020044)
MUSASHI_NATIVE_MIPS_WORD(0x3C050001)
MUSASHI_NATIVE_MIPS_WORD(0x34420002)
MUSASHI_NATIVE_MIPS_WORD(0x0C05200E)
MUSASHI_NATIVE_MIPS_WORD(0xAE020044)
MUSASHI_NATIVE_MIPS_WORD(0x0C051D18)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x0C051EB5)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x0C051CFB)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C058506)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x1440000E)
MUSASHI_NATIVE_MIPS_WORD(0x34028000)
MUSASHI_NATIVE_MIPS_WORD(0x960300B8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14620007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C056669)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0566CF)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0805608E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x920501AA)
MUSASHI_NATIVE_MIPS_WORD(0x0C0557FE)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801581AC - 40 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_801473EC(s32 *a0);
extern void func_80161418(void *a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern int func_80155FF8(int arg, int a1);

void func_801581AC(s32 a0) {
    s32 reserved[4];
    (void)reserved;
    *(s32 *)(a0 + 0x44) |= 2;
    func_80148038(a0, 0x10000);
    func_80147460(a0);
    func_80147AD4(a0, 0, 0, 0);
    func_801473EC((s32 *)a0);
    {
        register s32 ret __asm__("$2");
        func_80161418((void *)a0);
        __asm__ __volatile__("" : "=r"(ret));
        if (ret != 0) {
            return;
        }
    }
    if (*(u16 *)(a0 + 0xB8) == 0x8000) {
        func_801599A4((void *)a0);
        func_80159B3C((void *)a0);
    } else {
        func_80155FF8(a0, *(u8 *)(a0 + 0x1AA));
    }
}
#endif

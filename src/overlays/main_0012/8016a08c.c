/* Overlay range [8016A08C,8016A1CC) from MAIN.CD member 0012.
 * SHA256(span)=52fd67dfe63353c8e5a918821f20d57d2a5fca15dde63ae49f09d340a9fafc8e.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x90428EBF)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8016A08C - 80 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u8 D_80078EBF;
extern void func_80148534(s32 a0, s32 a1);
extern void func_8016A290();
extern void func_80147324(s32 arg0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80147364();
extern void func_80146C3C();

void func_8016A08C(s32 param_1) {
    register s32 s0 __asm__("$16");
    register void *s1 __asm__("$17");
    u8 buf20[8];
    u8 buf18[8];
    s32 iVar4;
    s16 sVar2;
    s0 = param_1;
    if (D_80078EBF != 0) {
        s1 = buf18;
        ((void (*)(void *, void *))func_80148534)(buf20, s1);
        *(s32 *)(s0 + 0x30) = (s32)(u32)D_80078EBF - 0x18;
        if ((s32)((u32)D_80078EBF - 0x18) >= 0) {
            func_8016A290(s0, buf20, s1);
            iVar4 = *(s32 *)(s0 + 0x1C) + 1;
            *(s32 *)(s0 + 0x1C) = iVar4;
            if (iVar4 == 4) {
                func_80147324(0x44C);
            }
            if (D_80078EBF < 0x80) {
                sVar2 = 0;
                do {
                    sVar2 = sVar2 + 1;
                } while (sVar2 < 2);
                ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x17, s0, (s32)*(s16 *)(s0 + 6), (s32)*(s16 *)(s0 + 0xA),
                              (s32)*(s16 *)(s0 + 0xE), 0, 0);
            } else {
                if (*(s16 *)(s0 + 0x2A) == 0) {
                    *(s16 *)(s0 + 0x2A) = 1;
                    *(s32 *)(s0 + 0x1C) = 0x100;
                }
                if ((*(u32 *)(s0 + 0x1C) & 0x1F) == 0) {
                    func_80147324(0x44D);
                }
            }
        }
    } else {
        ((void (*)(s32, s32))func_80147364)(4, 0x44C);
        ((void (*)(s32))func_80146C3C)(s0);
    }
}
#endif

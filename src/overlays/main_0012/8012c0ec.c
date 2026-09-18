/* Overlay range [8012C0EC,8012C194) from MAIN.CD member 0012.
 * SHA256(span)=82cc2ccbce6e3f1ba28d2f581e360ac6bcc0645ad2bc55eb6c5d3878b5e8d05c.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8C4274D4)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8012C0EC - 42 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 D_801274D4;
extern s16 D_80126CAC;
extern s32 D_801274E0;
extern s32 func_80013478(s32 a0, s32 a1);
extern void func_8012C218(void *a0);

s32 func_8012C0EC(s32 a0) {
    s32 (*fp)(s32) = (s32 (*)(s32))D_801274D4;
    s32 cond;
    s32 *p;
    if (fp == 0) {
        cond = (func_80013478(a0 + 4, (s32)&D_80126CAC) < D_801274E0) ^ 1;
    } else {
        cond = fp(a0);
    }
    if (cond == 0) {
        return 0;
    }
    p = *(s32 **)(a0 + 0x68);
    if (p != 0) {
        if ((*(s16 *)(a0 + 0x72) & 0x8000) != 0) {
            *(u16 *)((s32)p + 0xA) = *(u16 *)((s32)p + 0xA) & 0x7FFF;
        }
    }
    func_8012C218((void *)a0);
    return 1;
}
#endif

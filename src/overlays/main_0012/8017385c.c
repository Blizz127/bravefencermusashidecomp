/* Overlay range [8017385C,801738D4) from MAIN.CD member 0012.
 * SHA256(span)=bf9e9540620440af595eece571b60db5887b74797e9429ab9232337ff8f6b8ca.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x84636B30)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8017385C - 30 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s16 D_80126B30;
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);

void func_8017385C(u8 *a0) {
    switch (D_80126B30) {
    case 0:
    default:
        *(u16 *)(a0 + 0xAC) |= 0x80;
        *(u16 *)(a0 + 0xAA) |= 0x80;
        break;
    case 1:
        *(u16 *)(a0 + 0xAC) |= 0x10;
        *(u16 *)(a0 + 0xAA) |= 0x10;
        break;
    }
    func_80171A1C(a0);
    func_80174650((s32)a0);
}
#endif

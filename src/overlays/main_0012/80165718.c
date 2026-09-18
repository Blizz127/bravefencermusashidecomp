/* Overlay range [80165718,80165770) from MAIN.CD member 0012.
 * SHA256(span)=09763157ecfa85525712bfc7092447e9a3b82ce0e18560ef96a8e5e9efa94be3.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C038008)
MUSASHI_NATIVE_MIPS_WORD(0x90638EC1)
MUSASHI_NATIVE_MIPS_WORD(0x2402000C)
MUSASHI_NATIVE_MIPS_WORD(0x1062000B)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x2862000D)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x24020003)
MUSASHI_NATIVE_MIPS_WORD(0x10620006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x080595D8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24020018)
MUSASHI_NATIVE_MIPS_WORD(0x14620003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C059688)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80165718 - 22 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_80165A20(s32 a0);
extern u8 D_80078EC1;

void func_80165718(s32 a0) {
    switch (D_80078EC1) {
    case 3:
    case 0xC:
    case 0x18:
        func_80165A20(a0);
        break;
    }
}
#endif

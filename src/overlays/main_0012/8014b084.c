/* Overlay range [8014B084,8014B12C) from MAIN.CD member 0012.
 * SHA256(span)=959d1420d5cf4f69afdbb86b5a7e123a2e0dcfcf50b05d1293936943f0ed6409.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x94428EAC)
MUSASHI_NATIVE_MIPS_WORD(0x3C038008)
MUSASHI_NATIVE_MIPS_WORD(0x90638EBA)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8014B084 - 42 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u16 D_80078EAC;
extern u8 D_80078EBA;
extern void func_800D10EC(void);
extern void func_8002AC98(void);
extern void func_80145C54(void);

void func_8014B084(void) {
    u16 a;
    u8 b;
    a = D_80078EAC + 1;
    b = D_80078EBA + 1;
    D_80078EAC = a;
    D_80078EBA = b;
    if (a >= 0x16E) {
        D_80078EAC = 1;
    }
    D_80078EBA = b % 7;
    func_800D10EC();
    func_8002AC98();
    func_80145C54();
}
#endif

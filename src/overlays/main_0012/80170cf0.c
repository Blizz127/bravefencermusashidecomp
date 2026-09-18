/* Overlay range [80170CF0,80170D68) from MAIN.CD member 0012.
 * SHA256(span)=4110076ec7398b3d4ceba2226712998d947ec99582ff6beab01773b0f1e01f95.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8C42F738)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x92030217)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x10620007)
MUSASHI_NATIVE_MIPS_WORD(0x28620002)
MUSASHI_NATIVE_MIPS_WORD(0x1440000D)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x10620007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0805C355)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C048012)
MUSASHI_NATIVE_MIPS_WORD(0x8C84F73C)
MUSASHI_NATIVE_MIPS_WORD(0x0805C353)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C048012)
MUSASHI_NATIVE_MIPS_WORD(0x8C84F740)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C62B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80170CF0 - 30 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_801718AC(void *a0);

void func_80170CF0(void* a0)
{
    extern void *D_8011F738;
    extern s32 D_8011F73C;
    extern s32 D_8011F740;
    s32 v1;
    void *p;
    ((void (*)(s32))D_8011F738)(a0);
    v1 = *(u8 *)(a0 + 0x217);
    if (v1 == 1) {
        goto case_1;
    }
    if (v1 <= 1) {
        goto done;
    }
    if (v1 == 2) {
        goto case_2;
    }
    goto done;
case_1:
    p = (*(void * *)&D_8011F73C);
    goto call;
case_2:
    p = (*(void * *)&D_8011F740);
call:
    func_801718AC(p);
done:
    ;
}
#endif

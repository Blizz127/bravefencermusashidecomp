/* Overlay range [8012C750,8012C820) from MAIN.CD member 0012.
 * SHA256(span)=aaba1aa9d53e7fa7446ec324df0da75cd4d454f8764899643559619e551f6757.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x9482000A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420800)
MUSASHI_NATIVE_MIPS_WORD(0x1040000F)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x24630194)
MUSASHI_NATIVE_MIPS_WORD(0x24656480)
MUSASHI_NATIVE_MIPS_WORD(0x10A3001B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x94A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400018)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FEF4)
MUSASHI_NATIVE_MIPS_WORD(0x14A3FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0804B1FB)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x24630194)
MUSASHI_NATIVE_MIPS_WORD(0x0804B1EF)
MUSASHI_NATIVE_MIPS_WORD(0x2465658C)
MUSASHI_NATIVE_MIPS_WORD(0x0804B1FB)
MUSASHI_NATIVE_MIPS_WORD(0x00602821)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x246302A0)
MUSASHI_NATIVE_MIPS_WORD(0x10650008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x94620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1040FFF7)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2463010C)
MUSASHI_NATIVE_MIPS_WORD(0x1465FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x14A00003)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x0804B204)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x9482000A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x34428000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B224)
MUSASHI_NATIVE_MIPS_WORD(0xA482000A)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8012C750 - 52 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u8 D_80120194[];
extern u8 D_801202A0[];
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);

s32 func_8012C750(s32 a0)
{
    s32 p;
    s32 it;
    s32 v0;
    if (*(u16 *)(a0 + 0xA) & 0x800) {
        s32 base = (s32)D_80120194;
        p = base + 0x6480;
        if (p != base) {
            do {
                if (*(u16 *)p == 0) goto found;
                p -= 0x10C;
            } while (p != base);
        }
        p = 0;
        goto found;
    } else {
        it = (s32)D_80120194;
        __asm__ __volatile__("" : "=r"(it) : "0"(it));
        p = it + 0x658C;
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        __asm__ __volatile__("" : "=r"(it) : "0"(it));
        if (it == p) goto zero;
    body:
        if (*(u16 *)it == 0) goto copy;
        it += 0x10C;
        if (it != p) goto body;
    zero:
        p = 0;
    }
found:
    if (p == 0) {
        v0 = 0;
    } else {
        *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) | 0x8000;
        v0 = func_8012C890(a0, p, 0);
    }
    return v0;
}
#endif

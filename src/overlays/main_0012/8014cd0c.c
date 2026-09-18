/* Overlay range [8014CD0C,8014CD80) from MAIN.CD member 0012.
 * SHA256(span)=299c24a99d7b7d992331e14595c2594662ec8fac414724d07d98ceb85f4140b1.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x94820006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20018)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x9482000A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2443FFFD)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30012)
MUSASHI_NATIVE_MIPS_WORD(0x9483000E)
MUSASHI_NATIVE_MIPS_WORD(0x24420005)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001A)
MUSASHI_NATIVE_MIPS_WORD(0xA7A3001C)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30014)
MUSASHI_NATIVE_MIPS_WORD(0x8C820174)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400005)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x0C0533C1)
MUSASHI_NATIVE_MIPS_WORD(0x27A60018)
MUSASHI_NATIVE_MIPS_WORD(0x0805335C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C053360)
MUSASHI_NATIVE_MIPS_WORD(0x27A60018)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8014CD0C - 29 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_8014CF04(s32 a0, s32 a1, void *a2);
extern int func_8014CD80(s32 a0, u16 *a1, u16 *a2);

void func_8014CD0C(u8 *a0) {
    u16 sp10[3];
    u16 sp18[3];
    u16 b;
    u16 c;
    u16 d;
    b = *(u16 *)(a0 + 0x6);
    sp18[0] = b;
    sp10[0] = b;
    c = *(u16 *)(a0 + 0xA);
    sp10[1] = c - 3;
    d = *(u16 *)(a0 + 0xE);
    sp18[1] = c + 5;
    sp18[2] = d;
    sp10[2] = d;
    if (*(s32 *)(a0 + 0x174) == 0) {
        func_8014CF04((s32)a0, sp10, sp18);
    } else {
        func_8014CD80((s32)a0, sp10, sp18);
    }
}
#endif

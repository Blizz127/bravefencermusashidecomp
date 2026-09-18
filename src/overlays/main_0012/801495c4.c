/* Overlay range [801495C4,8014964C) from MAIN.CD member 0012.
 * SHA256(span)=f5d20636eae03d2a20a77820d58e826d92f7446a05387f2430243a1db78f0d96.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00028)
MUSASHI_NATIVE_MIPS_WORD(0x00A08021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF002C)
MUSASHI_NATIVE_MIPS_WORD(0x96020002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x96020006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20012)
MUSASHI_NATIVE_MIPS_WORD(0x9602000A)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20014)
MUSASHI_NATIVE_MIPS_WORD(0x8C840020)
MUSASHI_NATIVE_MIPS_WORD(0x27A60020)
MUSASHI_NATIVE_MIPS_WORD(0x0C04BC53)
MUSASHI_NATIVE_MIPS_WORD(0x24840034)
MUSASHI_NATIVE_MIPS_WORD(0x27A40020)
MUSASHI_NATIVE_MIPS_WORD(0x0C04BBDC)
MUSASHI_NATIVE_MIPS_WORD(0x27A50018)
MUSASHI_NATIVE_MIPS_WORD(0x97A20018)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA6020002)
MUSASHI_NATIVE_MIPS_WORD(0x97A2001A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA6020006)
MUSASHI_NATIVE_MIPS_WORD(0x97A2001C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA602000A)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF002C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00028)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0030)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801495C4 - 34 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_8014964C(s32 param_1, s32 param_2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012EF70(s32, s32);

void func_801495C4(s32 a0, s32 a1) {
    s16 in[4];
    s16 result[4];
    s16 buf[4];
    s16 *pin;
    s16 *m1;
    s16 *m2;
    s32 mtx;
    in[0] = *(u16 *)(a1 + 0x2);
    in[1] = *(u16 *)(a1 + 0x6);
    in[2] = *(u16 *)(a1 + 0xA);
    pin = in;                  __asm__ __volatile__("" : "=r"(pin) : "0"(pin));
    mtx = *(s32 *)(a0 + 0x20); __asm__ __volatile__("" : "=r"(mtx) : "0"(mtx));
    m1 = buf;                  __asm__ __volatile__("" : "=r"(m1) : "0"(m1));
    ((void (*)(s32, void *, void *))func_8012F14C)(mtx + 0x34, pin, m1);
    m2 = buf;                  __asm__ __volatile__("" : "=r"(m2) : "0"(m2));
    ((void (*)(void *, void *))func_8012EF70)(m2, result);
    *(s16 *)(a1 + 0x2) = result[0];
    *(s16 *)(a1 + 0x6) = result[1];
    *(s16 *)(a1 + 0xA) = result[2];
}
#endif

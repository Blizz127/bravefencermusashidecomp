/* Overlay range [801576A8,8015771C) from MAIN.CD member 0012.
 * SHA256(span)=4c754538e52e5c4f3ffda0e4635356902f397767f93a4f5abc52b2d01f3eaaa3.
 * Word export for the native seam; the body below is a
 * verified MATCH (29/29 words at 0x801576A8, -O2). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00020)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x8E020044)
MUSASHI_NATIVE_MIPS_WORD(0x960300B8)
MUSASHI_NATIVE_MIPS_WORD(0x34420002)
MUSASHI_NATIVE_MIPS_WORD(0xAE020044)
MUSASHI_NATIVE_MIPS_WORD(0x34028000)
MUSASHI_NATIVE_MIPS_WORD(0x14620007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C056669)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0566CF)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x08055DC2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C058482)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x14400004)
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

/* Verified byte-exact against retail by tools/match_function.py
 * (29/29 words at 0x801576A8). Twin of func_80155E30: same dead
 * `s32 du[4]` for the 16 phantom frame bytes. Codegen constraint,
 * not a source claim. Other types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */

void func_80155FF8(void *, u8);                  /* static */
void func_801599A4();                            /* static */
void func_80159B3C(void *);                      /* static */
s32 func_80161208(void *);                          /* static */

void func_801576A8(void *arg0) {
    s32 du[4];
    (void) &du;
    M2C_FIELD(arg0, s32 *, 0x44) = (s32) (M2C_FIELD(arg0, s32 *, 0x44) | 2);
    if (M2C_FIELD(arg0, u16 *, 0xB8) == 0x8000) {
        func_801599A4();
        func_80159B3C(arg0);
        return;
    }
    if (func_80161208(arg0) == 0) {
        func_80155FF8(arg0, M2C_FIELD(arg0, u8 *, 0x1AA));
    }
}
#endif

/* Main-exec range [80058BF4,80058C34) from the SLUS executable.
 * SHA256(span)=989e22de97bafa071af6e3638dbec38c1545850e3aac1e25377883f8434f3acc.
 * Word export for the native seam (m2c produced no draft). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x30C5003F)
MUSASHI_NATIVE_MIPS_WORD(0x30C6FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C048007)
MUSASHI_NATIVE_MIPS_WORD(0x24843F98)
MUSASHI_NATIVE_MIPS_WORD(0x00052900)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C422784)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00063182)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void D_80072784();
extern s32 D_80073F98;

void func_80058BF4(s32 arg0) {
    D_80072784(D_80073F98, (arg0 & 0x3F) * 0x10, (u32) (arg0 & 0xFFFF) >> 6);
}
#endif

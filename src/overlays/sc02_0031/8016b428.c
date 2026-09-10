/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016B428,8016B448).
 * Offset 0x432D0 at overlay base 80128158. SHA256(span)=ac5e410cbe7d3209dd40afae8cfeab8178fb8545dfad91d4bfb834d4dfd91278.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016b428.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05AD12)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8016B428 (main_0012.s), decoded manually from
 * raw asm (0x20 bytes; m2c arg placement corrected: the jal delay
 * slot zeroes a1 while a0 still holds the incoming argument, so
 * the call is B448(arg0, 0), not B448(0); NOT verified against
 * retail; C89-gated only, promotion requires an oracle MATCH). */

extern void func_8016B448(void *arg0, s32 arg1);

void func_8016B428(void *arg0) {
    func_8016B448(arg0, 0);
}
#endif

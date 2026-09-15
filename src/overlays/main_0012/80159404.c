/* Overlay range [80159404,80159434) from MAIN.CD member 0012.
 * SHA256(span)=72b600294eeaa32fac3f7e155c7c759c3cc65c627a72368e52c179f60af62cae.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C860020)
MUSASHI_NATIVE_MIPS_WORD(0x94830236)
MUSASHI_NATIVE_MIPS_WORD(0x94C20012)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x30420FFF)
MUSASHI_NATIVE_MIPS_WORD(0xA4C20012)
MUSASHI_NATIVE_MIPS_WORD(0x8C820234)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00451023)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820234)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80159404(void *arg0, s32 arg1) {
    void *temp_a2;

    temp_a2 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_a2, u16 *, 0x12) = (u16) ((M2C_FIELD(temp_a2, u16 *, 0x12) + M2C_FIELD(arg0, u16 *, 0x236)) & 0xFFF);
    M2C_FIELD(arg0, s32 *, 0x234) = (s32) (M2C_FIELD(arg0, s32 *, 0x234) - arg1);
}
#endif

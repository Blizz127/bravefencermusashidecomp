/* Main-exec range [80052430,80052454) from the SLUS executable.
 * SHA256(span)=e7c83d5bccd6bc52a2f15133283c464864c5087e31234fa07c436e2946e8eac4.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8CA80000)
MUSASHI_NATIVE_MIPS_WORD(0x8CA90004)
MUSASHI_NATIVE_MIPS_WORD(0x8CAA0008)
MUSASHI_NATIVE_MIPS_WORD(0xAC880014)
MUSASHI_NATIVE_MIPS_WORD(0xAC890018)
MUSASHI_NATIVE_MIPS_WORD(0xAC8A001C)
MUSASHI_NATIVE_MIPS_WORD(0x00801021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void *func_80052430(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) M2C_FIELD(arg1, s32 *, 8);
    return arg0;
}
#endif

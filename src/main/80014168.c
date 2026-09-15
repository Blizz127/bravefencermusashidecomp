/* Main-exec range [80014168,800141AC) from the SLUS executable.
 * SHA256(span)=e057702a93e921a02421e5ec73b0279ffe91b95496c440c5d8ca7d111918d253.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x00A03021)
MUSASHI_NATIVE_MIPS_WORD(0x88C20003)
MUSASHI_NATIVE_MIPS_WORD(0x98C20000)
MUSASHI_NATIVE_MIPS_WORD(0x88C30007)
MUSASHI_NATIVE_MIPS_WORD(0x98C30004)
MUSASHI_NATIVE_MIPS_WORD(0xABA20013)
MUSASHI_NATIVE_MIPS_WORD(0xBBA20010)
MUSASHI_NATIVE_MIPS_WORD(0xABA30017)
MUSASHI_NATIVE_MIPS_WORD(0xBBA30014)
MUSASHI_NATIVE_MIPS_WORD(0x0C0123EF)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80048FBC(void *, void *);           /* static */

void func_80014168(void *arg1) {
    s32 sp17;
    s32 sp13;
    s32 sp10;
    sp13 = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    sp17 = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    func_80048FBC(&sp10, arg1);
}
#endif

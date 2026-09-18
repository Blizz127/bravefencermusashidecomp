/* Main-exec range [8003A098,8003A0D0) from the SLUS executable.
 * SHA256(span)=0b8ef50584290b9d27fb04342a75c3848adf2668fe679ee86eb0d7558276c435.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00052C00)
MUSASHI_NATIVE_MIPS_WORD(0x8C830000)
MUSASHI_NATIVE_MIPS_WORD(0x00052C03)
MUSASHI_NATIVE_MIPS_WORD(0x24620001)
MUSASHI_NATIVE_MIPS_WORD(0xAC820000)
MUSASHI_NATIVE_MIPS_WORD(0x00051040)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0x00021040)
MUSASHI_NATIVE_MIPS_WORD(0x90630000)
MUSASHI_NATIVE_MIPS_WORD(0x00822021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA083001A)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8003A098(u8 **arg0, s16 arg1) {
    u8 *temp_v1;

    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    arg0 = (u8 **) ((u8 *) arg0 + (arg1 * 0x1A));
    M2C_FIELD(arg0, u8 *, 0x1A) = (u8) *temp_v1;
}
#endif

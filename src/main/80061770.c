/* Main-exec range [80061770,800617CC) from the SLUS executable.
 * SHA256(span)=1b2bb78c42f96d251b3ce9c7fde2065040d9282d8c6a035432a57ee2f9d33271.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x00A03821)
MUSASHI_NATIVE_MIPS_WORD(0x3C058007)
MUSASHI_NATIVE_MIPS_WORD(0x24A5472C)
MUSASHI_NATIVE_MIPS_WORD(0x88A20003)
MUSASHI_NATIVE_MIPS_WORD(0x98A20000)
MUSASHI_NATIVE_MIPS_WORD(0x80A30004)
MUSASHI_NATIVE_MIPS_WORD(0x80A40005)
MUSASHI_NATIVE_MIPS_WORD(0xA8E20003)
MUSASHI_NATIVE_MIPS_WORD(0xB8E20000)
MUSASHI_NATIVE_MIPS_WORD(0xA0E30004)
MUSASHI_NATIVE_MIPS_WORD(0xA0E40005)
MUSASHI_NATIVE_MIPS_WORD(0x04C10002)
MUSASHI_NATIVE_MIPS_WORD(0x00C01021)
MUSASHI_NATIVE_MIPS_WORD(0x24C2000F)
MUSASHI_NATIVE_MIPS_WORD(0x00021103)
MUSASHI_NATIVE_MIPS_WORD(0x24430030)
MUSASHI_NATIVE_MIPS_WORD(0x00021100)
MUSASHI_NATIVE_MIPS_WORD(0x00C21023)
MUSASHI_NATIVE_MIPS_WORD(0x24420030)
MUSASHI_NATIVE_MIPS_WORD(0xA0E30002)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0E20003)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_8007472C;

void func_80061770(s32 arg0, void *arg1) {
    s32 temp_v0;
    s32 var_v0;

    M2C_FIELD(arg1, s8 *, 3) = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    M2C_FIELD(arg1, s8 *, 4) = (s8) M2C_FIELD(D_8007472C, s8 *, 4);
    M2C_FIELD(arg1, s8 *, 5) = (s8) M2C_FIELD(D_8007472C, s8 *, 5);
    var_v0 = arg0;
    if (arg0 < 0) {
        var_v0 = arg0 + 0xF;
    }
    temp_v0 = var_v0 >> 4;
    M2C_FIELD(arg1, s8 *, 2) = (s8) (temp_v0 + 0x30);
    M2C_FIELD(arg1, s8 *, 3) = (s8) ((arg0 - (temp_v0 * 0x10)) + 0x30);
}
#endif

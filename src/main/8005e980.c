/* Main-exec range [8005E980,8005E9D4) from the SLUS executable.
 * SHA256(span)=5723444f8ed9550770b865e0f14a8f5d25947300c939487a3347148402333e53.
 * Word export for the native seam (m2c produced no draft). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x90830046)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x10620005)
MUSASHI_NATIVE_MIPS_WORD(0x24020003)
MUSASHI_NATIVE_MIPS_WORD(0x10620009)
MUSASHI_NATIVE_MIPS_WORD(0x2402004D)
MUSASHI_NATIVE_MIPS_WORD(0x08017A73)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24020044)
MUSASHI_NATIVE_MIPS_WORD(0xA0820036)
MUSASHI_NATIVE_MIPS_WORD(0x24820051)
MUSASHI_NATIVE_MIPS_WORD(0xAC82002C)
MUSASHI_NATIVE_MIPS_WORD(0x08017A73)
MUSASHI_NATIVE_MIPS_WORD(0xA0830035)
MUSASHI_NATIVE_MIPS_WORD(0xA0820036)
MUSASHI_NATIVE_MIPS_WORD(0x2482005D)
MUSASHI_NATIVE_MIPS_WORD(0xAC82002C)
MUSASHI_NATIVE_MIPS_WORD(0x24020006)
MUSASHI_NATIVE_MIPS_WORD(0xA0820035)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8005E980(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x46);
    switch (temp_v1) {                              /* irregular */
    case 2:
        M2C_FIELD(arg0, s8 *, 0x36) = 0x44;
        M2C_FIELD(arg0, void **, 0x2C) = (void *) (arg0 + 0x51);
        M2C_FIELD(arg0, u8 *, 0x35) = temp_v1;
        return;
    case 3:
        M2C_FIELD(arg0, s8 *, 0x36) = 0x4D;
        M2C_FIELD(arg0, void **, 0x2C) = (void *) (arg0 + 0x5D);
        M2C_FIELD(arg0, u8 *, 0x35) = 6U;
        return;
    }
}
#endif

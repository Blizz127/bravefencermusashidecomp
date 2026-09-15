/* Overlay range [80147948,8014799C) from MAIN.CD member 0012.
 * SHA256(span)=b8162a120ca51f9d3e10eae932a8a61cc292f8faead422f3517ca2e93f1459ce.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C820024)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0x04A10007)
MUSASHI_NATIVE_MIPS_WORD(0xAC820024)
MUSASHI_NATIVE_MIPS_WORD(0x00061823)
MUSASHI_NATIVE_MIPS_WORD(0x0062102A)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x08051E65)
MUSASHI_NATIVE_MIPS_WORD(0xAC830024)
MUSASHI_NATIVE_MIPS_WORD(0x18A00007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C820024)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0046102A)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAC860024)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80147948(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x24) + arg1;
    M2C_FIELD(arg0, s32 *, 0x24) = temp_v0;
    if (arg1 < 0) {
        temp_v1 = -arg2;
        if (temp_v1 >= temp_v0) {
            M2C_FIELD(arg0, s32 *, 0x24) = temp_v1;
            return;
        }
    }
    if ((arg1 > 0) && (M2C_FIELD(arg0, s32 *, 0x24) >= arg2)) {
        M2C_FIELD(arg0, s32 *, 0x24) = arg2;
    }
}
#endif

/* Overlay range [80147A30,80147A84) from MAIN.CD member 0012.
 * SHA256(span)=1fd43414d8af7593c79d3a969808ff5f12410123bf4dbcc5a4f6dbd695af722f.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C82002C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0x04A10007)
MUSASHI_NATIVE_MIPS_WORD(0xAC82002C)
MUSASHI_NATIVE_MIPS_WORD(0x00061823)
MUSASHI_NATIVE_MIPS_WORD(0x0062102A)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x08051E9F)
MUSASHI_NATIVE_MIPS_WORD(0xAC83002C)
MUSASHI_NATIVE_MIPS_WORD(0x18A00007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C82002C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0046102A)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAC86002C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80147A30(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x2C) + arg1;
    M2C_FIELD(arg0, s32 *, 0x2C) = temp_v0;
    if (arg1 < 0) {
        temp_v1 = -arg2;
        if (temp_v1 >= temp_v0) {
            M2C_FIELD(arg0, s32 *, 0x2C) = temp_v1;
            return;
        }
    }
    if ((arg1 > 0) && (M2C_FIELD(arg0, s32 *, 0x2C) >= arg2)) {
        M2C_FIELD(arg0, s32 *, 0x2C) = arg2;
    }
}
#endif

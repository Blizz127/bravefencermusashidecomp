/* Overlay range [80149228,80149284) from MAIN.CD member 0012.
 * SHA256(span)=6530bb5b9ca01736f1940ee02055f5de226a14aad03eb215c8400c889efc991d.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x848201E4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x948201E6)
MUSASHI_NATIVE_MIPS_WORD(0xAC8001DC)
MUSASHI_NATIVE_MIPS_WORD(0xAC8001E0)
MUSASHI_NATIVE_MIPS_WORD(0xA48201E4)
MUSASHI_NATIVE_MIPS_WORD(0x948500AC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10A00007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C8201E0)
MUSASHI_NATIVE_MIPS_WORD(0x948301E6)
MUSASHI_NATIVE_MIPS_WORD(0xAC8501E0)
MUSASHI_NATIVE_MIPS_WORD(0x00A21024)
MUSASHI_NATIVE_MIPS_WORD(0xA48301E4)
MUSASHI_NATIVE_MIPS_WORD(0xAC8201DC)
MUSASHI_NATIVE_MIPS_WORD(0x948201E4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA48201E4)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80149228(void *arg0) {
    s32 temp_v0;
    u16 temp_a1;

    if (M2C_FIELD(arg0, s16 *, 0x1E4) == 0) {
        M2C_FIELD(arg0, s32 *, 0x1DC) = 0;
        M2C_FIELD(arg0, s32 *, 0x1E0) = 0;
        M2C_FIELD(arg0, s16 *, 0x1E4) = (s16) M2C_FIELD(arg0, u16 *, 0x1E6);
    }
    temp_a1 = M2C_FIELD(arg0, u16 *, 0xAC);
    if (temp_a1 != 0) {
        temp_v0 = M2C_FIELD(arg0, s32 *, 0x1E0);
        M2C_FIELD(arg0, s32 *, 0x1E0) = (s32) temp_a1;
        M2C_FIELD(arg0, s16 *, 0x1E4) = (s16) M2C_FIELD(arg0, u16 *, 0x1E6);
        M2C_FIELD(arg0, s32 *, 0x1DC) = (s32) (temp_a1 & temp_v0);
    }
    M2C_FIELD(arg0, s16 *, 0x1E4) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1E4) - 1);
}
#endif

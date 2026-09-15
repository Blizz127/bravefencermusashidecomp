/* Overlay range [8012B260,8012B2CC) from MAIN.CD member 0012.
 * SHA256(span)=923438ed3a64e5e895d91851d7d19730c530762c27217ac15a6bf6d11a82bea4.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x94820006)
MUSASHI_NATIVE_MIPS_WORD(0x94830050)
MUSASHI_NATIVE_MIPS_WORD(0x8C850020)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20008)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0xACA20048)
MUSASHI_NATIVE_MIPS_WORD(0x9482000A)
MUSASHI_NATIVE_MIPS_WORD(0x94830052)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0xA4A2000A)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0xACA2004C)
MUSASHI_NATIVE_MIPS_WORD(0x9482000E)
MUSASHI_NATIVE_MIPS_WORD(0x94A3002C)
MUSASHI_NATIVE_MIPS_WORD(0x94840054)
MUSASHI_NATIVE_MIPS_WORD(0x34630001)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0xA4A2000C)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0xA4A3002C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACA20050)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8012B260(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x20);
    temp_v0 = M2C_FIELD(arg0, u16 *, 6) + M2C_FIELD(arg0, u16 *, 0x50);
    M2C_FIELD(temp_a1, s16 *, 8) = temp_v0;
    M2C_FIELD(temp_a1, s32 *, 0x48) = (s32) temp_v0;
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0xA) + M2C_FIELD(arg0, u16 *, 0x52);
    M2C_FIELD(temp_a1, s16 *, 0xA) = temp_v0_2;
    M2C_FIELD(temp_a1, s32 *, 0x4C) = (s32) temp_v0_2;
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0xE) + M2C_FIELD(arg0, u16 *, 0x54);
    M2C_FIELD(temp_a1, s16 *, 0xC) = temp_v0_3;
    M2C_FIELD(temp_a1, u16 *, 0x2C) = (u16) (M2C_FIELD(temp_a1, u16 *, 0x2C) | 1);
    M2C_FIELD(temp_a1, s32 *, 0x50) = (s32) temp_v0_3;
}
#endif

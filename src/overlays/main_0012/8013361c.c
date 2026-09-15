/* Overlay range [8013361C,801336E8) from MAIN.CD member 0012.
 * SHA256(span)=5544766a570733e9d1fdebff2b079f7ad7eb84dadc86c1770d82ff4c9ca75157.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x84830004)
MUSASHI_NATIVE_MIPS_WORD(0x84C90000)
MUSASHI_NATIVE_MIPS_WORD(0x84A20006)
MUSASHI_NATIVE_MIPS_WORD(0x84E80000)
MUSASHI_NATIVE_MIPS_WORD(0x00691821)
MUSASHI_NATIVE_MIPS_WORD(0x00481021)
MUSASHI_NATIVE_MIPS_WORD(0x0043102A)
MUSASHI_NATIVE_MIPS_WORD(0x14400029)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x84830006)
MUSASHI_NATIVE_MIPS_WORD(0x84A20004)
MUSASHI_NATIVE_MIPS_WORD(0x00691821)
MUSASHI_NATIVE_MIPS_WORD(0x00481021)
MUSASHI_NATIVE_MIPS_WORD(0x0062182A)
MUSASHI_NATIVE_MIPS_WORD(0x14600022)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8483000C)
MUSASHI_NATIVE_MIPS_WORD(0x84C90004)
MUSASHI_NATIVE_MIPS_WORD(0x84A2000E)
MUSASHI_NATIVE_MIPS_WORD(0x84E80004)
MUSASHI_NATIVE_MIPS_WORD(0x00691821)
MUSASHI_NATIVE_MIPS_WORD(0x00481021)
MUSASHI_NATIVE_MIPS_WORD(0x0043102A)
MUSASHI_NATIVE_MIPS_WORD(0x14400019)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8483000E)
MUSASHI_NATIVE_MIPS_WORD(0x84A2000C)
MUSASHI_NATIVE_MIPS_WORD(0x00691821)
MUSASHI_NATIVE_MIPS_WORD(0x00481021)
MUSASHI_NATIVE_MIPS_WORD(0x0062182A)
MUSASHI_NATIVE_MIPS_WORD(0x14600012)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x84830008)
MUSASHI_NATIVE_MIPS_WORD(0x84C60002)
MUSASHI_NATIVE_MIPS_WORD(0x84A2000A)
MUSASHI_NATIVE_MIPS_WORD(0x84E70002)
MUSASHI_NATIVE_MIPS_WORD(0x00661821)
MUSASHI_NATIVE_MIPS_WORD(0x00471021)
MUSASHI_NATIVE_MIPS_WORD(0x0043102A)
MUSASHI_NATIVE_MIPS_WORD(0x14400009)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8483000A)
MUSASHI_NATIVE_MIPS_WORD(0x84A20008)
MUSASHI_NATIVE_MIPS_WORD(0x00661821)
MUSASHI_NATIVE_MIPS_WORD(0x00471021)
MUSASHI_NATIVE_MIPS_WORD(0x0062182A)
MUSASHI_NATIVE_MIPS_WORD(0x14600002)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8013361C(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_t0;
    s16 temp_t0_2;
    s16 temp_t1;
    s16 temp_t1_2;
    s32 var_v0;

    temp_t1 = M2C_FIELD(arg2, s16 *, 0);
    temp_t0 = M2C_FIELD(arg3, s16 *, 0);
    var_v0 = 0;
    if ((M2C_FIELD(arg1, s16 *, 6) + temp_t0) >= (M2C_FIELD(arg0, s16 *, 4) + temp_t1)) {
        var_v0 = 0;
        if ((M2C_FIELD(arg0, s16 *, 6) + temp_t1) >= (M2C_FIELD(arg1, s16 *, 4) + temp_t0)) {
            temp_t1_2 = M2C_FIELD(arg2, s16 *, 4);
            temp_t0_2 = M2C_FIELD(arg3, s16 *, 4);
            var_v0 = 0;
            if ((M2C_FIELD(arg1, s16 *, 0xE) + temp_t0_2) >= (M2C_FIELD(arg0, s16 *, 0xC) + temp_t1_2)) {
                var_v0 = 0;
                if ((M2C_FIELD(arg0, s16 *, 0xE) + temp_t1_2) >= (M2C_FIELD(arg1, s16 *, 0xC) + temp_t0_2)) {
                    temp_a2 = M2C_FIELD(arg2, s16 *, 2);
                    temp_a3 = M2C_FIELD(arg3, s16 *, 2);
                    var_v0 = 0;
                    if ((M2C_FIELD(arg1, s16 *, 0xA) + temp_a3) >= (M2C_FIELD(arg0, s16 *, 8) + temp_a2)) {
                        var_v0 = 0;
                        if ((M2C_FIELD(arg0, s16 *, 0xA) + temp_a2) >= (M2C_FIELD(arg1, s16 *, 8) + temp_a3)) {
                            var_v0 = 1;
                        }
                    }
                }
            }
        }
    }
    return var_v0;
}
#endif

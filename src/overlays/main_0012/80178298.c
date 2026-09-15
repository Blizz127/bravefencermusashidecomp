/* Overlay range [80178298,801783D0) from MAIN.CD member 0012.
 * SHA256(span)=877e1f8f1fc80ad2f24d89d606edc8d64e55129f8ba2fcd01675a091464bd149.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2C420080)
MUSASHI_NATIVE_MIPS_WORD(0x10400048)
MUSASHI_NATIVE_MIPS_WORD(0x00804821)
MUSASHI_NATIVE_MIPS_WORD(0x240A0008)
MUSASHI_NATIVE_MIPS_WORD(0x24880012)
MUSASHI_NATIVE_MIPS_WORD(0x84A30000)
MUSASHI_NATIVE_MIPS_WORD(0x24023870)
MUSASHI_NATIVE_MIPS_WORD(0x10620015)
MUSASHI_NATIVE_MIPS_WORD(0x28623871)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x24021850)
MUSASHI_NATIVE_MIPS_WORD(0x1062000C)
MUSASHI_NATIVE_MIPS_WORD(0x24021858)
MUSASHI_NATIVE_MIPS_WORD(0x1062000B)
MUSASHI_NATIVE_MIPS_WORD(0x24C20004)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0CE)
MUSASHI_NATIVE_MIPS_WORD(0xA506FFF6)
MUSASHI_NATIVE_MIPS_WORD(0x24023871)
MUSASHI_NATIVE_MIPS_WORD(0x1062000D)
MUSASHI_NATIVE_MIPS_WORD(0x24023872)
MUSASHI_NATIVE_MIPS_WORD(0x1062000E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0CE)
MUSASHI_NATIVE_MIPS_WORD(0xA506FFF6)
MUSASHI_NATIVE_MIPS_WORD(0x24C20004)
MUSASHI_NATIVE_MIPS_WORD(0xA502FFF6)
MUSASHI_NATIVE_MIPS_WORD(0x24E2FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0D7)
MUSASHI_NATIVE_MIPS_WORD(0xA502FFF8)
MUSASHI_NATIVE_MIPS_WORD(0x24C60008)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0ED)
MUSASHI_NATIVE_MIPS_WORD(0x24A50002)
MUSASHI_NATIVE_MIPS_WORD(0x24C60004)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0ED)
MUSASHI_NATIVE_MIPS_WORD(0x24A50002)
MUSASHI_NATIVE_MIPS_WORD(0x24C60002)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0ED)
MUSASHI_NATIVE_MIPS_WORD(0x24A50002)
MUSASHI_NATIVE_MIPS_WORD(0xA507FFF8)
MUSASHI_NATIVE_MIPS_WORD(0x84A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28420861)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0805E0D7)
MUSASHI_NATIVE_MIPS_WORD(0x24C60008)
MUSASHI_NATIVE_MIPS_WORD(0x24C60007)
MUSASHI_NATIVE_MIPS_WORD(0x3C0300FF)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C046480)
MUSASHI_NATIVE_MIPS_WORD(0x34848080)
MUSASHI_NATIVE_MIPS_WORD(0x2522FFEC)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x3C030400)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0xAD220000)
MUSASHI_NATIVE_MIPS_WORD(0xAD04FFF2)
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x25290014)
MUSASHI_NATIVE_MIPS_WORD(0xA102FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x90A30000)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x24024056)
MUSASHI_NATIVE_MIPS_WORD(0xA502FFFC)
MUSASHI_NATIVE_MIPS_WORD(0xA50AFFFE)
MUSASHI_NATIVE_MIPS_WORD(0xA50A0000)
MUSASHI_NATIVE_MIPS_WORD(0xA103FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x25080014)
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2C420080)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFBC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x01201021)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 *func_80178298(s32 *arg0, u8 *arg1, s16 arg2, s16 arg3) {
    s16 temp_v1;
    s16 var_a2;
    s16 var_v0;
    s32 *var_t1;
    u8 *var_a1;
    u8 temp_v1_2;
    void *var_t0;

    var_a1 = arg1;
    var_a2 = arg2;
    var_t1 = arg0;
    if ((u8) *var_a1 < 0x80U) {
        var_t0 = arg0 + 0x12;
        do {
            temp_v1 = var_a1->unk0;
            if (temp_v1 != 0x3870) {
                if (temp_v1 < 0x3871) {
                    if (temp_v1 != 0x1850) {
                        var_v0 = var_a2 + 4;
                        if (temp_v1 != 0x1858) {
                            var_t0->unk-A = var_a2;
                            goto block_15;
                        }
                        goto block_11;
                    }
                    var_v0 = var_a2 + 4;
block_11:
                    var_t0->unk-A = var_v0;
                    var_t0->unk-8 = (s16) (arg3 - 7);
                    goto block_18;
                }
                if (temp_v1 != 0x3871) {
                    if (temp_v1 != 0x3872) {
                        var_t0->unk-A = var_a2;
block_15:
                        var_t0->unk-8 = arg3;
                        if (var_a1->unk0 >= 0x861) {
                            var_a2 += 8;
                        } else {
                            var_a2 += 7;
                        }
block_18:
                        *var_t1 = ((var_t1 - 0x14) & 0xFFFFFF) | 0x04000000;
                        var_t0->unk-E = 0x64808080;
                        var_t1 += 0x14;
                        var_t0->unk-6 = (u8) var_a1->unk0;
                        temp_v1_2 = var_a1->unk1;
                        var_a1 = var_a1 + 1 + 1;
                        var_t0->unk-4 = 0x4056;
                        var_t0->unk-2 = 8;
                        var_t0->unk0 = 8;
                        var_t0->unk-5 = temp_v1_2;
                        var_t0 += 0x14;
                    } else {
                        var_a2 += 2;
                        var_a1 += 2;
                    }
                } else {
                    var_a2 += 4;
                    var_a1 += 2;
                }
            } else {
                var_a2 += 8;
                var_a1 += 2;
            }
        } while ((u8) *var_a1 < 0x80U);
    }
    return var_t1;
}
#endif

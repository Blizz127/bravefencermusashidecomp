/* Overlay range [8013A8FC,8013A9B4) from MAIN.CD member 0012.
 * SHA256(span)=6c7e34d58f42f98e0d613b261ef29c6f62085e5bdf597696de09f8dfcb005842.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x94820018)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400007)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x0804EA69)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x2442DA80)
MUSASHI_NATIVE_MIPS_WORD(0x0804EA5B)
MUSASHI_NATIVE_MIPS_WORD(0x00A22821)
MUSASHI_NATIVE_MIPS_WORD(0x8C820040)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1440001B)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0x00250821)
MUSASHI_NATIVE_MIPS_WORD(0x8422DA80)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1040FFF2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24A50010)
MUSASHI_NATIVE_MIPS_WORD(0x28A20020)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF7)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x10A0000D)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x94830018)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28620007)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10600006)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04EA6D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0804EA69)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8013A9B4(void *);                      /* static */
extern s32 *D_8011DA80;

s32 func_8013A8FC(void *arg0) {
    s32 var_a1;
    u16 temp_v1;
    void *var_a1_2;

    if (M2C_FIELD(arg0, u16 *, 0x18) == 0) {
        return 1;
    }
    if (M2C_FIELD(arg0, s32 *, 0x40) == 0) {
        var_a1 = 0;
loop_5:
        if (*(&D_8011DA80 + var_a1) != 0) {
            var_a1 += 0x10;
            if (var_a1 >= 0x20) {
                var_a1_2 = 0;
            } else {
                goto loop_5;
            }
        } else {
            var_a1_2 = var_a1 + &D_8011DA80;
        }
        if (var_a1_2 != 0) {
            temp_v1 = M2C_FIELD(arg0, u16 *, 0x18);
            if ((s32) temp_v1 < 7) {
                if (temp_v1 != 0) {
                    func_8013A9B4(var_a1_2);
                    return 1;
                }
                /* Duplicate return node #13. Try simplifying control flow for better match */
                return 0;
            }
            /* Duplicate return node #13. Try simplifying control flow for better match */
            return 0;
        }
        /* Duplicate return node #13. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
#endif

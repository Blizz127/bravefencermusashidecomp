/* Exact retail word export for [80018E9C,80018F20); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x24428D98)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x14820017)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x94428DCA)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420100)
MUSASHI_NATIVE_MIPS_WORD(0x1040000E)
MUSASHI_NATIVE_MIPS_WORD(0x240400E2)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A46D)
MUSASHI_NATIVE_MIPS_WORD(0x240400E2)
MUSASHI_NATIVE_MIPS_WORD(0x24500001)
MUSASHI_NATIVE_MIPS_WORD(0x320200FF)
MUSASHI_NATIVE_MIPS_WORD(0x2C42005A)
MUSASHI_NATIVE_MIPS_WORD(0x14400005)
MUSASHI_NATIVE_MIPS_WORD(0x240400E2)
MUSASHI_NATIVE_MIPS_WORD(0x00008021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A35E)
MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0x240400E2)
MUSASHI_NATIVE_MIPS_WORD(0x080063C1)
MUSASHI_NATIVE_MIPS_WORD(0x320500FF)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A468)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80028D78();                                 /* static */
void func_800291A0(s32, s32);                            /* static */
s32 func_800291B4();                               /* static */
extern s32 *D_80078D98;
extern u16 D_80078DCA;

void func_80018E9C(s32 arg0) {
    s32 var_a1;
    s32 var_s0;

    if (arg0 == &D_80078D98) {
        if (D_80078DCA & 0x100) {
            var_s0 = func_800291B4(0xE2) + 1;
            if ((u32) (var_s0 & 0xFF) >= 0x5AU) {
                var_s0 = 0;
                func_80028D78(1);
            }
            var_a1 = var_s0 & 0xFF;
        } else {
            var_a1 = 0;
        }
        func_800291A0(0xE2, var_a1);
    }
}
#endif

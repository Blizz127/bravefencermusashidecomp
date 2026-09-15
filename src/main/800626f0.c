/* Main-exec range [800626F0,80062760) from the SLUS executable.
 * SHA256(span)=f003400ded362efe88eb5280b550eb1aa3b91fc44f7153b12241d35f51e4c491.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC3F8D18)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24090057)
MUSASHI_NATIVE_MIPS_WORD(0x240A00B0)
MUSASHI_NATIVE_MIPS_WORD(0x0140F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C42016C)
MUSASHI_NATIVE_MIPS_WORD(0x2409000B)
MUSASHI_NATIVE_MIPS_WORD(0x20430884)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC238D20)
MUSASHI_NATIVE_MIPS_WORD(0x20430894)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC238D24)
MUSASHI_NATIVE_MIPS_WORD(0xAC400594)
MUSASHI_NATIVE_MIPS_WORD(0x24420004)
MUSASHI_NATIVE_MIPS_WORD(0x2529FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x1520FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C01738A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C1F8008)
MUSASHI_NATIVE_MIPS_WORD(0x8FFF8D18)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
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

void func_8005CE28();                                  /* static */
void func_8005CF08();                                  /* static */
extern s32 D_80078D18;
extern s32 jtbl_80078D20_main;
extern s32 jtbl_80078D24_main;

void func_800626F0(void) {
    s32 var_t1;
    void *var_v0;

    D_80078D18 = saved_reg_ra;
    func_8005CF08();
    var_v0 = (void *(*)())0xB0()->unk16C;
    var_t1 = 0xB;
    jtbl_80078D20_main = var_v0 + 0x884;
    jtbl_80078D24_main = var_v0 + 0x894;
    do {
        var_v0->unk594 = 0;
        var_v0 += 4;
        var_t1 -= 1;
    } while (var_t1 != 0);
    func_8005CE28();
}
#endif

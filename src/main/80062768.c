/* Main-exec range [80062768,800627D0) from the SLUS executable.
 * SHA256(span)=390a79d6b0f5b07d58195244152147f2cc8a4928ef78bfe1f4d6e36f8aca1507.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC3F8D28)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24090057)
MUSASHI_NATIVE_MIPS_WORD(0x240A00B0)
MUSASHI_NATIVE_MIPS_WORD(0x0140F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x240A0009)
MUSASHI_NATIVE_MIPS_WORD(0x8C42016C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2043062C)
MUSASHI_NATIVE_MIPS_WORD(0xAC600000)
MUSASHI_NATIVE_MIPS_WORD(0x24630004)
MUSASHI_NATIVE_MIPS_WORD(0x254AFFFF)
MUSASHI_NATIVE_MIPS_WORD(0x1540FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C01738A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C6)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C1F8008)
MUSASHI_NATIVE_MIPS_WORD(0x8FFF8D28)
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
void func_8005CF18();                                  /* static */
extern s32 D_80078D28;

void func_80062768(void) {
    s32 *var_v1;
    s32 var_t2;

    D_80078D28 = saved_reg_ra;
    func_8005CF08();
    var_t2 = 9;
    var_v1 = (void *(*)())0xB0()->unk16C + 0x62C;
    do {
        *var_v1 = 0;
        var_v1 += 4;
        var_t2 -= 1;
    } while (var_t2 != 0);
    func_8005CE28();
    func_8005CF18();
}
#endif

/* Overlay range [80153978,801539F8) from MAIN.CD member 0012.
 * SHA256(span)=e45b24cb1096642c9f5441bb042f195cf6ed026e7e0612d8de1a42cd190c9b46.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF001C)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00018)
MUSASHI_NATIVE_MIPS_WORD(0x94A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x94A20002)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x2442001F)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20012)
MUSASHI_NATIVE_MIPS_WORD(0x94A20004)
MUSASHI_NATIVE_MIPS_WORD(0x27A60010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04CDE1)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20014)
MUSASHI_NATIVE_MIPS_WORD(0x24032000)
MUSASHI_NATIVE_MIPS_WORD(0x1443000B)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x93A20016)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400007)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C054E7E)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_80133784(s32, u16 *);                        /* static */
s32 func_801539F8(s32, u16 *);                      /* static */

s32 func_80153978(s32 arg0, void *arg1) {
    u16 sp14;
    s16 sp12;
    u16 sp10;
    s32 var_v0;

    sp10 = arg1->unk0;
    sp12 = arg1->unk2 + 0x1F;
    sp14 = arg1->unk4;
    var_v0 = 1;
    if (func_80133784(0, &sp10) == 0x2000) {
        var_v0 = 1;
        if (sp16 == 0) {
            var_v0 = 1;
            if (func_801539F8(arg0, &sp10) == 0) {
                var_v0 = 0;
            }
        }
    }
    return var_v0;
}
#endif

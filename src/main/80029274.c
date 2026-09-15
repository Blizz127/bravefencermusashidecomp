/* Exact retail word export for [80029274,8002931C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFF68)
MUSASHI_NATIVE_MIPS_WORD(0x03A03821)
MUSASHI_NATIVE_MIPS_WORD(0x3C068007)
MUSASHI_NATIVE_MIPS_WORD(0x24C62C84)
MUSASHI_NATIVE_MIPS_WORD(0x24C80090)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC30004)
MUSASHI_NATIVE_MIPS_WORD(0x8CC40008)
MUSASHI_NATIVE_MIPS_WORD(0x8CC5000C)
MUSASHI_NATIVE_MIPS_WORD(0xACE20000)
MUSASHI_NATIVE_MIPS_WORD(0xACE30004)
MUSASHI_NATIVE_MIPS_WORD(0xACE40008)
MUSASHI_NATIVE_MIPS_WORD(0xACE5000C)
MUSASHI_NATIVE_MIPS_WORD(0x24C60010)
MUSASHI_NATIVE_MIPS_WORD(0x14C8FFF6)
MUSASHI_NATIVE_MIPS_WORD(0x24E70010)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC30004)
MUSASHI_NATIVE_MIPS_WORD(0xACE20000)
MUSASHI_NATIVE_MIPS_WORD(0xACE30004)
MUSASHI_NATIVE_MIPS_WORD(0x3C078008)
MUSASHI_NATIVE_MIPS_WORD(0x24E78E78)
MUSASHI_NATIVE_MIPS_WORD(0x03A03021)
MUSASHI_NATIVE_MIPS_WORD(0x27A80090)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC30004)
MUSASHI_NATIVE_MIPS_WORD(0x8CC40008)
MUSASHI_NATIVE_MIPS_WORD(0x8CC5000C)
MUSASHI_NATIVE_MIPS_WORD(0xACE20000)
MUSASHI_NATIVE_MIPS_WORD(0xACE30004)
MUSASHI_NATIVE_MIPS_WORD(0xACE40008)
MUSASHI_NATIVE_MIPS_WORD(0xACE5000C)
MUSASHI_NATIVE_MIPS_WORD(0x24C60010)
MUSASHI_NATIVE_MIPS_WORD(0x14C8FFF6)
MUSASHI_NATIVE_MIPS_WORD(0x24E70010)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC30004)
MUSASHI_NATIVE_MIPS_WORD(0xACE20000)
MUSASHI_NATIVE_MIPS_WORD(0xACE30004)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0098)
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

extern s32 D_80072C84;
extern s32 *D_80078E78;

void func_80029274(void) {
    s32 sp90;
    s32 (*var_a2)();
    void *var_a3_2;
    void *var_a2_2;
    void *var_a3;

    var_a3 = sp;
    var_a2 = D_80072C84;
    do {
        var_a3->unk0 = (s32) var_a2->unk0;
        var_a3->unk4 = (s32) var_a2->unk4;
        var_a3->unk8 = (s32) var_a2->unk8;
        var_a3->unkC = (s32) var_a2->unkC;
        var_a2 += 0x10;
        var_a3 += 0x10;
    } while (var_a2 != (D_80072C84 + 0x90));
    var_a3->unk0 = (s32) var_a2->unk0;
    var_a3->unk4 = (s32) var_a2->unk4;
    var_a3_2 = &D_80078E78;
    var_a2_2 = sp;
    do {
        var_a3_2->unk0 = (s32) var_a2_2->unk0;
        var_a3_2->unk4 = (s32) var_a2_2->unk4;
        var_a3_2->unk8 = (s32) var_a2_2->unk8;
        var_a3_2->unkC = (s32) var_a2_2->unkC;
        var_a2_2 += 0x10;
        var_a3_2 += 0x10;
    } while (var_a2_2 != &sp90);
    var_a3_2->unk0 = (s32) var_a2_2->unk0;
    var_a3_2->unk4 = (s32) var_a2_2->unk4;
}
#endif

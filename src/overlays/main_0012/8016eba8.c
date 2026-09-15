/* Overlay range [8016EBA8,8016EC0C) from MAIN.CD member 0012.
 * SHA256(span)=e3de14ee3bd25e256ef7a1fba01ca72daca7d85f8d9d0a942e149d652dd21078.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x92020002)
MUSASHI_NATIVE_MIPS_WORD(0x96030004)
MUSASHI_NATIVE_MIPS_WORD(0x00021040)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x94221740)
MUSASHI_NATIVE_MIPS_WORD(0x24050080)
MUSASHI_NATIVE_MIPS_WORD(0x00621823)
MUSASHI_NATIVE_MIPS_WORD(0x0C05BB03)
MUSASHI_NATIVE_MIPS_WORD(0xA6030004)
MUSASHI_NATIVE_MIPS_WORD(0x92030002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x246200FF)
MUSASHI_NATIVE_MIPS_WORD(0x14600002)
MUSASHI_NATIVE_MIPS_WORD(0xA2020002)
MUSASHI_NATIVE_MIPS_WORD(0xA2000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
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

extern s32 D_80181740;
void func_8016EC0C();                                 /* static */

void func_8016EBA8(void *arg0) {
    u8 temp_v1;

    arg0->unk4 = (u16) (arg0->unk4 - *(D_80181740 + (arg0->unk2 * 2)));
    func_8016EC0C(0x80);
    temp_v1 = arg0->unk2;
    arg0->unk2 = (u8) (temp_v1 + 0xFF);
    if (temp_v1 == 0) {
        arg0->unk0 = 0;
    }
}
#endif

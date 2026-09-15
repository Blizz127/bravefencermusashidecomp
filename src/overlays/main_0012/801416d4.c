/* Overlay range [801416D4,80141788) from MAIN.CD member 0012.
 * SHA256(span)=28cbd8a32d2ba355ac7d6718bef12b2e82b6571ef0f23dc08b6a3683b82c36ea.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C038011)
MUSASHI_NATIVE_MIPS_WORD(0x9063514D)
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x9042515C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00620018)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x24060002)
MUSASHI_NATIVE_MIPS_WORD(0x00042400)
MUSASHI_NATIVE_MIPS_WORD(0x00042403)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x9042514C)
MUSASHI_NATIVE_MIPS_WORD(0x00003812)
MUSASHI_NATIVE_MIPS_WORD(0x00472821)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x10820010)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0x28820002)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10800007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x080505DE)
MUSASHI_NATIVE_MIPS_WORD(0x00031400)
MUSASHI_NATIVE_MIPS_WORD(0x1086000B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x080505DE)
MUSASHI_NATIVE_MIPS_WORD(0x00031400)
MUSASHI_NATIVE_MIPS_WORD(0x0C03447C)
MUSASHI_NATIVE_MIPS_WORD(0x30A400FF)
MUSASHI_NATIVE_MIPS_WORD(0x080505DD)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x0C034596)
MUSASHI_NATIVE_MIPS_WORD(0x30A400FF)
MUSASHI_NATIVE_MIPS_WORD(0x080505DD)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x0C050703)
MUSASHI_NATIVE_MIPS_WORD(0x24040006)
MUSASHI_NATIVE_MIPS_WORD(0x24030001)
MUSASHI_NATIVE_MIPS_WORD(0x00031400)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_800D11F0(s32, s32, s32, s32);                /* extern */
s32 func_800D1658(s32, s32, s32, s32);                /* extern */
void func_80141C0C(s32, s32, s32, s32);                    /* static */
extern u8 D_8011514C;
extern u8 D_8011514D;
extern u8 D_8011515C;

s32 func_801416D4(s16 arg0) {
    s32 temp_a1;
    s32 temp_lo;
    s32 var_v0;
    s32 var_v1;

    temp_lo = D_8011514D * D_8011515C;
    temp_a1 = D_8011514C + temp_lo;
    if (arg0 != 1) {
        if (arg0 < 2) {
            if (arg0 != 0) {
                var_v0 = 0 << 0x10;
            } else {
                var_v1 = func_800D11F0(temp_a1 & 0xFF, temp_a1, 2, temp_lo);
                goto block_9;
            }
        } else if (arg0 != 2) {
            var_v0 = 0 << 0x10;
        } else {
            func_80141C0C(6, temp_a1, 2, temp_lo);
            var_v1 = 1;
            goto block_9;
        }
    } else {
        var_v1 = func_800D1658(temp_a1 & 0xFF, temp_a1, 2, temp_lo);
block_9:
        var_v0 = var_v1 << 0x10;
    }
    return var_v0 >> 0x10;
}
#endif

/* Native retail instruction export [8005F728,8005F75C).
 * Verified against asm/main.s and the extracted EXE. No C match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028006)
MUSASHI_NATIVE_MIPS_WORD(0x2442F75C)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC222974)
MUSASHI_NATIVE_MIPS_WORD(0x3C028006)
MUSASHI_NATIVE_MIPS_WORD(0x2442FB70)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC222978)
MUSASHI_NATIVE_MIPS_WORD(0x3C028006)
MUSASHI_NATIVE_MIPS_WORD(0x2442F830)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC22297C)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_8005F75C;
extern s32 *D_8005F830;
extern s32 D_80072978;
extern s32 D_8007297C;
extern s32 func_8005FB70;
extern s32 func_80072974;

void func_8005F728(void) {
    func_80072974 = &D_8005F75C;
    D_80072978 = func_8005FB70;
    D_8007297C = &D_8005F830;
}
#endif

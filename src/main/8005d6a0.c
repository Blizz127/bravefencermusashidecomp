/* Native retail instruction export [8005D6A0,8005D6CC).
 * Verified against asm/main.s and the extracted EXE. No C match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x2442898C)
MUSASHI_NATIVE_MIPS_WORD(0x3C038006)
MUSASHI_NATIVE_MIPS_WORD(0x2463D734)
MUSASHI_NATIVE_MIPS_WORD(0xAC430000)
MUSASHI_NATIVE_MIPS_WORD(0x3C038006)
MUSASHI_NATIVE_MIPS_WORD(0x2463D6CC)
MUSASHI_NATIVE_MIPS_WORD(0xAC430004)
MUSASHI_NATIVE_MIPS_WORD(0xAC40FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC400008)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_8005D734;
extern s32 D_8005D6CC;
extern s32 *D_8007898C;

void func_8005D6A0(void) {
    M2C_FIELD(&D_8007898C, void **, 0) = &D_8005D734;
    M2C_FIELD(&D_8007898C, void **, 4) = &D_8005D6CC;
    M2C_FIELD(&D_8007898C, s32 *, -4) = 0;
    M2C_FIELD(&D_8007898C, s32 *, 8) = 0;
}
#endif

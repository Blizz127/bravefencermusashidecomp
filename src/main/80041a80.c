/* Exact retail word export for [80041A80,80041AB0); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00C03821)
MUSASHI_NATIVE_MIPS_WORD(0x00052C00)
MUSASHI_NATIVE_MIPS_WORD(0x00052C03)
MUSASHI_NATIVE_MIPS_WORD(0x0C0106AC)
MUSASHI_NATIVE_MIPS_WORD(0x24060001)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 func_80041AB0(s32, s32, s32, s32);

/* m2c dropped the leading `$a0` passthrough and the trailing `$a3 = $a2`
 * duplicate: the callee takes four arguments. The `(s16)` cast on the
 * middle argument and on the return are what emit the `sll`/`sra`
 * pairs around the call. */
s16 func_80041A80(s32 arg0, s32 arg1, s32 arg2) {
    return (s16)func_80041AB0(arg0, (s16)arg1, 1, arg2);
}
#endif

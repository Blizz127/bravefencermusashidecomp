/* SC02.CD FILE_031 / ov_SC02_031 retail span [80157F64,80157FC4).
 * Offset 0x2FE0C at overlay base 80128158. SHA256(span)=30ce95e166041ff97067e8581b293285d37196a91c8d4da409d568f121fe25c2.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80157f64.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A45E)
MUSASHI_NATIVE_MIPS_WORD(0x24040087)
MUSASHI_NATIVE_MIPS_WORD(0x304200FF)
MUSASHI_NATIVE_MIPS_WORD(0x1040000B)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C052200)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x30420080)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05272D)
MUSASHI_NATIVE_MIPS_WORD(0x24050005)
MUSASHI_NATIVE_MIPS_WORD(0x08055FEC)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_80029178();                               /* extern */
s32 func_80148800(s32);                             /* static */
void func_80149CB4(s32, s32);                            /* static */

s32 func_80157F64(s32 arg0) {
    if (func_80029178(0x87) & 0xFF) {
        if (func_80148800(arg0) & 0x80) {
            func_80149CB4(arg0, 5);
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
#endif

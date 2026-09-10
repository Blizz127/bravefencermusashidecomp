/* SC02.CD FILE_031 / ov_SC02_031 retail span [801724EC,8017250C).
 * Offset 0x4A394 at overlay base 80128158. SHA256(span)=d7a64ba9faeb4ce0944d0d9786bcaadb7fedc85d36e8995e9d410aa004f6be85.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801724ec.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C004D14)
MUSASHI_NATIVE_MIPS_WORD(0x24840004)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x28420010)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
#else
#include "psx_types.h"

s32 func_80013450(s32);                             /* extern */

s32 func_801724EC(s32 arg0) {
    return func_80013450(arg0 + 4) < 0x10;
}
#endif

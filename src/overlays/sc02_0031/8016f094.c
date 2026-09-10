/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016F094,8016F0AC).
 * Offset 0x46F3C at overlay base 80128158. SHA256(span)=9028eee09a4afe806e5c89e6679fc1f0fadc1abe804563ed1661c02e7c67aaa5.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016f094.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C03FBFF)
MUSASHI_NATIVE_MIPS_WORD(0x8C8201F8)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC8201F8)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x1F8]; s32 flags; } T;
void func_8016F094(T *p) {
    p->flags &= ~0x04000000;
}
#endif

/* SC02.CD FILE_031 / ov_SC02_031 retail span [80156648,80156670).
 * Offset 0x2E4F0 at overlay base 80128158. SHA256(span)=3f54c39eb256c3bde5eea91bf813e0d39c0b35fa89b3dd39996b3660c74f055c.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80156648.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0xA08001A8)
MUSASHI_NATIVE_MIPS_WORD(0xA08001A9)
MUSASHI_NATIVE_MIPS_WORD(0x0C055A85)
MUSASHI_NATIVE_MIPS_WORD(0xA08001C0)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
void func_80156A14();
typedef struct { u8 pad[0x1A8]; u8 a, b; u8 pad1AA[0x1C0-0x1AA]; u8 c; } T;
void func_80156648(T *p) {
    p->a = 0;
    p->b = 0;
    p->c = 0;
    func_80156A14(p);
}
#endif

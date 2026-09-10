/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013E67C,8013E6AC).
 * Offset 0x16524 at overlay base 80128158. SHA256(span)=709298e7b4efaa95c215861226a4fa227ee5a0882dcf1852b6fa74c2bab3e561.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8013e67c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C034928)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3C028014)
MUSASHI_NATIVE_MIPS_WORD(0x2442E5E8)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xAC22DB24)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Recovered from member0012 and verified byte-exact by match_function.py.
 * Types describe the observed call/store, not original source declarations.
 * D_8011DB24 belongs to the separately loaded member0010 address range;
 * it must remain shared storage in the native port. */
extern void func_800D24A0(s32);
extern void func_8013E5E8(void);
extern void (*D_8011DB24)(void);

void func_8013E67C(void) {
    func_800D24A0(0);
    D_8011DB24 = func_8013E5E8;
}
#endif

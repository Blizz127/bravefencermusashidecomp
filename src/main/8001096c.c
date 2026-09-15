/* Main-exec range [8001096C,8001099C) from the SLUS executable.
 * SHA256(span)=364c92601ff434347d2b4e1b8e71709ec1ca72648aae75d08844ea342ba56fac.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0xAFBE0010)
MUSASHI_NATIVE_MIPS_WORD(0x03A0F021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00B376)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03C0E821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FBE0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */
#ifdef MUSASHI_NATIVE_CALLBACK_HANDLER
#include "musashi_boot_memory.h"
int musashi_boot_call_8001096c(MusashiBootMemory *memory,
    MusashiGuestCallbackExecutor execute, void *userdata) {
    if (!memory) return 0;
    if (!execute || !execute(userdata, memory, 0x8002cdd8u)) return 0;
    return 1;
}
#else
void func_8002CDD8();                                  /* static */

void func_8001096C(void) {
    func_8002CDD8();
}
#endif
#endif

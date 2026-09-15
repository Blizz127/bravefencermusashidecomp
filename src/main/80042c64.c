/* Main-exec range [80042C64,80042C90) from the SLUS executable.
 * SHA256(span)=10a6fc24d646f22be8f184959bea92a50dba690615f6db08e6e1513d70c47e79.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0x10A00006)
MUSASHI_NATIVE_MIPS_WORD(0x24A2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x2403FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xAC800000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x1443FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x24840004)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Byte-exact callback-state clear [80042C64,80042C90). Count is words:
 * callback initialization passes 0x41A, clearing 0x1068 bytes. */
#ifdef MUSASHI_NATIVE_WORD_CLEAR_BINDING
#define CLEAR_WORD() do { \
    destination[0] = 0; destination[1] = 0; \
    destination[2] = 0; destination[3] = 0; \
    destination += 4; \
} while (0)
void func_80042C64_native(u8 *destination, u32 word_count) {
#else
#define CLEAR_WORD() (*destination++ = 0)
void func_80042C64(u32 *destination, u32 word_count) {
#endif
    while (word_count--)
        CLEAR_WORD();
}
#undef CLEAR_WORD
#endif

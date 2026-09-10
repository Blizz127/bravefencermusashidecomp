/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012BF4C,8012BF54).
 * Offset 0x3DF4 at overlay base 80128158. SHA256(span)=ab96ea14c4cd28075ba493ec7f9c5835812a77b78c5b86afd972b2b5adb04d37.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012bf4c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC85001C)
#else
#include "psx_types.h"

/* Word setter at vram 0x8012BF4C.
 *
 * Stores its second argument at byte offset 0x1C of the structure its first
 * argument points at. Indexing a word pointer by 7 reaches that offset without
 * needing the structure declared, which is not yet known.
 *
 * Signatures and types here are the loosest that reproduce the bytes; they are
 * not evidence of the original declaration.
 */
void func_8012BF4C(s32 *object, s32 value) {
    object[7] = value;
}
#endif

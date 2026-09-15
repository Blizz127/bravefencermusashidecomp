/* Main-exec range [8003A3D8,8003A404) from the SLUS executable.
 * SHA256(span)=d0c82ad7db2cc766e8ffc926f6c0975e143708bcf7d9a032f55b5d01f57feb80.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00041600)
MUSASHI_NATIVE_MIPS_WORD(0x00041A02)
MUSASHI_NATIVE_MIPS_WORD(0x306300FF)
MUSASHI_NATIVE_MIPS_WORD(0x00031C00)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x00041A02)
MUSASHI_NATIVE_MIPS_WORD(0x3063FF00)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x00042602)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00441025)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8003A3D8(u32 arg0) {
    return ((arg0 << 0x18) + (((arg0 >> 8) & 0xFF) << 0x10) + ((arg0 >> 8) & 0xFF00)) | (arg0 >> 0x18);
}
#endif

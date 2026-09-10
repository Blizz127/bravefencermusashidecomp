/* Exact retail [8001D0E8,8001D0F4).
 * Words from pinned SLUS_007.26.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xA4850028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA486002A)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x28]; s16 a; s16 b; } T;
void func_8001D0E8(T *p, s16 a1, s16 a2) { p->a = a1; p->b = a2; }
#endif

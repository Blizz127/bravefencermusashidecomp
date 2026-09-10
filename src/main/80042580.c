#include "psx_types.h"

/* Byte-exact indirect initialization wrapper [80042580,800425B0).
 * Initial slot +0C points to 80042718, but retain the table indirection.
 * This PS1 layout is not a host callback table. */
typedef struct {
    u8 opaque00[0xC];
    void *(*initialize)(void);
} CallbackDispatch;

/* Exact matched wrapper stream for the native MIPS diagnostic. It preserves
 * the guest table indirection; no host callback table is introduced. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
MUSASHI_NATIVE_MIPS_WORD(0x8c42cb84)
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x8c42000c)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040f809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif
extern CallbackDispatch *D_8006CB84;

void *func_80042580(void) {
    return D_8006CB84->initialize();
}

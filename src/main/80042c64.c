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

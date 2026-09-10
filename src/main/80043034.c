/* Byte-exact word clear used by DMA callback initialization. */
#include "psx_types.h"
void func_80043034(u32 *destination, u32 word_count) {
    while (word_count--)
        *destination++ = 0;
}

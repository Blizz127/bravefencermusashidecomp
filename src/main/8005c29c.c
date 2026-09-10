#include "psx_types.h"

/* Byte-exact graphics reset helper [8005C29C,8005C2C8). Byte storage and
 * unsigned countdown also permit this same body to run on bounded native RAM. */
void func_8005C29C(u8 *destination, s32 value, u32 count) {
    while (count--)
        *destination++ = value;
}

#include "psx_types.h"

extern u8 D_800AE648[];

/* Recovered from retail and verified byte-exact with gcc-2.7.2-psx -O2. */
#ifdef MUSASHI_NATIVE_TABLE_CLEAR_BINDING
void func_80029044_native(u8 *destination) {
    u32 var_v1 = 0;
    do {
        destination[var_v1] = 0;
        var_v1 += 1;
    } while (var_v1 < 0x40U);
}
#else
void func_80029044(void) {
    u32 var_v1 = 0;
    do {
        D_800AE648[var_v1] = 0;
        var_v1 += 1;
    } while (var_v1 < 0x40U);
}
#endif

#include "psx_types.h"

extern u8 D_800747C0[];
void func_80016714(u8 *, s32);

/* Recovered from retail and verified byte-exact with gcc-2.7.2-psx -O2. */
void func_8001903C(void) {
    func_80016714(D_800747C0, 8);
}

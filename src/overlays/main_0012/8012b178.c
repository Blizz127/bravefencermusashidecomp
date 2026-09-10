/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800484EC();
typedef struct { u8 pad[0x20]; u8 *inner; } T;
void func_8012B178(T *p, s32 a1) {
    s32 tmp[4];
    tmp[2] = a1;
    tmp[1] = 0;
    tmp[0] = 0;
    func_800484EC(p->inner + 0x34, tmp, (u8 *)p + 0x10);
}

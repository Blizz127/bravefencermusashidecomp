/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80150170();
void func_8014FE60();
typedef struct {
    u8 pad[6]; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
    u8 pad10[0x78]; s16 u88, u8A, u8C;
} T;
void func_8014FDF4(T *p) {
    if (p->u6 != p->u88 || p->uA != p->u8A || p->uE != p->u8C) {
        func_80150170();
        return;
    }
    func_8014FE60();
}

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80143458();
void func_8012931C();
s32 func_80128ED8();
void func_801292C8();
typedef struct {
    u8 pad[2]; u16 u2;
    u8 pad4[0x1C]; void *inner;
} T;
void func_801433F0(T *p) {
    if (p->u2 == 0) {
        func_80143458(p);
    } else {
        func_8012931C(p);
        if (func_80128ED8(p->inner, (u8 *)p + 0x24)) {
            func_801292C8(p);
        }
    }
}

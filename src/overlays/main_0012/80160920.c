/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
s32 func_801487F4();
void func_80160A74();
s32 func_80161208();
void func_80154150();
void func_80146CA0();
typedef struct { u16 idx; u8 pad[0xB6]; u16 b8; } T;
void func_80160920(T *p) {
    if ((func_801487F4(p) & 8) == 0) {
        D_80180A1C[p->idx](p);
        func_80160A74(p);
    } else if (func_80161208(p) == 0 && p->b8 == 0x8000) {
        func_80154150(p, 0x25);
        func_80146CA0(p);
    }
}

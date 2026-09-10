/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80161208();
void func_80154150();
void func_80154A74();
void func_80146CA0();
typedef struct { u8 pad[0xB8]; u16 f; } T;
void func_80160CB4(T *p) {
    if (func_80161208(p) == 0 && p->f == 0x8000) {
        func_80154150(p, 0x27);
        func_80154A74(p, 0x1F);
        func_80146CA0(p);
    }
}

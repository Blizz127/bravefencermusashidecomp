/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154150();
void func_80154A74();
void func_80146CA0();
void func_80161208();
typedef struct { u8 pad[0xB8]; u16 f; } T;
void func_80160244(T *p) {
    if (p->f == 0x8000) {
        func_80154150(p, 0x23);
        func_80154A74(p, 0x1B);
        func_80146CA0(p);
    } else {
        func_80161208(p);
    }
}

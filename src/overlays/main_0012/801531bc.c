/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80149020();
s32 func_801536DC();
void func_80146CA0();
typedef struct { u8 pad[0xDE]; u8 a, b; } T;
void func_801531BC(T *p) {
    func_80149020(p);
    if (func_801536DC(p) == 0) {
        p->a = 1;
        p->b = 0;
        func_80146CA0(p);
    }
}

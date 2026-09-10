/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80149AA8();
s32 func_80149B54();
void func_80146750();
typedef struct { s16 a, b, c, d; void *p; s32 x, y; } P;
s32 func_801498E0(void *obj) {
    P s;
    if (func_80149AA8(obj) || func_80149B54(obj)) {
        s.a = 8;
        s.p = obj;
        s.b = 0;
        s.c = -0x1E;
        s.d = 0;
        s.x = 0;
        s.y = 0;
        func_80146750(&s);
        return 1;
    }
    return 0;
}

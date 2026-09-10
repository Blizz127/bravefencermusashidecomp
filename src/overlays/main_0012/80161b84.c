/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80149884();
void func_801599A4();
void func_801498C0();
typedef struct { u8 pad[0x44]; s32 flags; } T;
s32 func_80161B84(T *p) {
    if (p->flags & 0x100) {
        if (func_80149884()) {
            func_801599A4(p);
            func_801498C0(p);
            return 1;
        }
    }
    return 0;
}

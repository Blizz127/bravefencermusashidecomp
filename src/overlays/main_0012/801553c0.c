/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80029178();
void func_8001D150();
typedef struct Inner { u8 pad[0x24]; s32 u24; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; u8 pad24[0x20]; s32 flags; } T;
void func_801553C0(T *p) {
    if ((p->flags & 4) || (u8)func_80029178(0x12F)) {
        p->flags &= 0xEFFFFFFF;
    } else {
        p->flags |= 0x10000000;
    }
    func_8001D150(p->inner->u24, 0x15);
}

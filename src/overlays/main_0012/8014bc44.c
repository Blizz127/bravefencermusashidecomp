/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014BC80();
extern u16 D_80078EB2;
typedef struct { u8 pad[0x44]; s32 flags; } T;
void func_8014BC44(T *p, s32 a1) {
    if (p->flags & 0x2000000) {
        a1 = D_80078EB2;
    }
    func_8014BC80(p, a1);
}

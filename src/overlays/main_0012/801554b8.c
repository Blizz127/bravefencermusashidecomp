/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_800D02D0();
void func_801659DC();
typedef struct { u8 pad[0x196]; u8 u196; u8 pad197[9]; u8 u1A0; } T;
s32 func_801554B8(T *p) {
    u8 v;
    v = p->u1A0;
    if (v == p->u196) {
        return 0;
    }
    if (func_800D02D0(v) == 0) {
        return 1;
    }
    p->u196 = p->u1A0;
    func_801659DC(p);
    return 0;
}

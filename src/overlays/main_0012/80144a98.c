/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8012C1B8();
void func_8012CAE4();
void func_8001C214();
typedef struct { s16 unk0, unk2; u8 pad4[0x1C]; s32 unk20; } T;
void func_80144A98(T *p) {
    s32 v = func_8012C1B8(p);
    p->unk20 = v;
    if (v == 0) {
        func_8012CAE4(p);
    } else {
        func_8001C214(v, 0);
        p->unk2 = 1;
    }
}

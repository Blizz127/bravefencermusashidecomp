/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800167B8();
typedef struct { u8 pad[0x15]; u8 unk15; } T;
s32 func_8015987C(T *p) {
    func_800167B8(4);
    p->unk15++;
    return 0;
}

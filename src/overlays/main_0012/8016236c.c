/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014706C();
extern s32 D_80126B58;
typedef struct { u8 pad[0x15]; u8 unk15; u8 pad16[0x28-0x16]; s32 unk28; } T;
s32 func_8016236C(T *p) {
    func_8014706C(&D_80126B58);
    p->unk28 = 0xA;
    p->unk15++;
    return 0;
}

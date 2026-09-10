/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154418();
typedef struct {
    u8 pad[0xB4]; s32 b4; s16 b8, ba; u8 bc, bd;
    u8 padBE[0x1E]; u8 dc;
} T;
void func_801542A4(T *p, s32 a1) {
    p->b4 = a1;
    p->ba = 1;
    p->b8 = 1;
    p->bc = 0;
    p->bd = 0;
    p->dc = 0;
    func_80154418(p);
}

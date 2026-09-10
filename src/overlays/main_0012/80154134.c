/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct {
    u8 pad[0xB4]; s32 b4; s16 b8, ba; u8 bc, bd;
    u8 padBE[0x1E]; u8 dc;
} T;
void func_80154134(T *p) {
    p->b4 = 0;
    p->ba = 0;
    p->b8 = 0;
    p->bd = 0;
    p->bc = 0;
    p->dc = 0;
}

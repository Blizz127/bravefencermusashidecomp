/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8014A51C();
void func_801477E8();
void func_80154274();
extern s32 D_800D4BE0;
extern s32 D_8011F730;
typedef struct {
    u8 pad[0xB4]; s32 uB4;
    u8 padB8[4]; u8 uBC;
    u8 padBD[0x109]; u8 u1C6;
    u8 pad1C7[0x75]; s32 u23C, u240;
    u8 u244;
} T;
s32 func_8015B858(T *p) {
    if (p->u1C6 || p->u240) {
        return 0;
    }
    if (func_8014A51C() == 0) {
        return 0;
    }
    p->u23C = p->uB4;
    p->u244 = p->uBC;
    func_801477E8(p, 0xFFF20000);
    func_80154274(p, &D_800D4BE0);
    D_8011F730 |= 2;
    return 1;
}

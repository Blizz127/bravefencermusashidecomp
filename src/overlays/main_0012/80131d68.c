/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80131E00();
s32 func_80131CA8();
void func_8002A04C();
void func_8012C218();
typedef struct { u8 pad[0x78]; s32 u78; } T;
s32 func_80131D68(T *p, s32 a1) {
    a1 = (u8)a1;
    if (a1 == 2 || a1 == 0x1B) {
        func_80131E00(p, 0x12);
        return 1;
    }
    if (a1 == 0x1A || a1 == 0x1C) {
        if (func_80131CA8(p, 0x11)) {
            return 1;
        }
        if (p->u78) {
            func_8002A04C(p);
        }
        func_8012C218(p);
        return 1;
    }
    return 0;
}

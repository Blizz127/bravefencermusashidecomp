/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
void func_80147078();
void func_80159B70();
void func_80154A74();
void func_80161208();
typedef struct { u16 idx; u8 pad[0xB6]; u16 b8, ba; } T;
void func_8015FE70(T *p) {
    if ((p->b8 & 0x8000) && p->ba == 0) {
        D_80180A1C[p->idx](p);
        func_80147078(p, 0);
        func_80159B70(p);
    } else {
        if (p->b8 & 0x8000) {
            p->b8 = p->ba;
        }
        if (p->b8 & 0x4000) {
            func_80154A74(p, 0x11);
        }
        func_80161208(p);
    }
}

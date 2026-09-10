/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
void func_8015E40C();
s32 func_80161B18();
s32 func_80161B84();
s32 func_80161208();
void func_8015E5B0();
void func_80147078();
void func_80159BE4();
typedef struct {
    u16 idx;
    u8 pad2[0xB6]; u16 b8;
    u8 padBA[0x17A]; s32 u234;
} T;
void func_8015E344(T *p) {
    func_8015E40C(p);
    if (func_80161B18(p)) {
        return;
    }
    if (func_80161B84(p)) {
        return;
    }
    if (func_80161208(p)) {
        return;
    }
    if (p->b8 & 0x4000) {
        func_8015E5B0(p);
        p->u234 = 1;
    }
    if (p->b8 & 0x8000) {
        D_80180A1C[p->idx](p);
        func_80147078(p, 0);
        func_80159BE4(p);
    }
}

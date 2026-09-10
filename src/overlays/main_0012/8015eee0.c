/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
void func_80148038();
void func_80147460();
void func_80147AD4();
void func_801473EC();
void func_80147078();
void func_80159B70();
s32 func_80161418();
void func_801725A4();
typedef struct { u16 idx; u8 pad[0xB6]; u16 b8; } T;
void func_8015EEE0(T *p) {
    func_80148038(p, 0x10000);
    func_80147460(p);
    func_80147AD4(p, 0, 0, 0x1000);
    func_801473EC(p);
    if (p->b8 & 0x8000) {
        D_80180A1C[p->idx](p);
        func_80147078(p, 0);
        func_80159B70(p);
    } else if (func_80161418(p) == 0) {
        func_801725A4(p);
    }
}

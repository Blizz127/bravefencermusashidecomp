/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
void func_80149FB0();
void func_8014FA04();
s32 func_8014E6A0();
void func_80147078();
void func_80159B70();
void func_801725F4();
void func_80146CA0();
typedef struct Inner { u8 pad[0x10]; s16 u10; } Inner;
typedef struct {
    u16 idx;
    u8 pad2[0x1E]; Inner *inner;
    u8 pad24[0x210]; s32 u234;
    u8 pad238[0xC]; s16 u244;
} T;
void func_8015D104(T *p) {
    func_80149FB0(p);
    func_8014FA04(p);
    if (func_8014E6A0(p) == 0) {
        D_80180A1C[p->idx](p);
        func_80147078(p, 0);
        func_80159B70(p);
    } else {
        func_801725F4(p);
        p->u234 = 0xFF1D0000;
        p->inner->u10 = 0x600;
        p->u244 = p->inner->u10;
        func_80146CA0(p);
    }
}

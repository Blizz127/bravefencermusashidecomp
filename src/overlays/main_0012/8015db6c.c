/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154150();
void func_80154A74();
void func_8015DCB8();
void func_80147300();
void func_801553A8();
void func_8014BD60();
void func_80146CA0();
typedef struct { u8 pad[0x234]; s32 f234; } T;
void func_8015DB6C(T *p) {
    func_80154150(p, 0x1C);
    func_80154A74(p, 0x19);
    p->f234 = 0;
    func_8015DCB8(p);
    func_80147300(0x5F5);
    func_801553A8(p);
    func_8014BD60(p, 4);
    func_80146CA0(p);
}

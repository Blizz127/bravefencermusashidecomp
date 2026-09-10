/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80184288;
extern s32 D_80184294;
extern s32 D_80184298;
void func_80147084();
void func_80147098();
void func_801470AC();
void func_80147078();
void func_80158880();
typedef struct { u8 pad[0xA8]; u8 fA8; } T;
void func_80158814(T *p) {
    D_80184288 = 0;
    D_80184294 = 1;
    D_80184298 = 0;
    p->fA8 = 0;
    func_80147084(p);
    func_80147098(p);
    func_801470AC(p);
    func_80147078(p, 0x1A);
    func_80158880(p);
}

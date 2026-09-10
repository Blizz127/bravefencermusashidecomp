/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80146E98();
void func_800D0F4C();
void func_8014BB24();
void func_8014BD24();
void *func_8013767C();
void func_80146CA0();
extern s32 D_80110EC0;
typedef struct { u8 pad[0x198]; void *p198; } T;
void func_80160F70(T *p) {
    if (func_80146E98(p)) {
        func_800D0F4C(0xA);
        func_8014BB24(p, 0x96, 0);
        func_8014BD24(p, 0x96);
        p->p198 = func_8013767C(&D_80110EC0);
        func_80146CA0(p);
    }
}

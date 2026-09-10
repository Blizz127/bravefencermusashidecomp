/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154150();
void func_801725E0();
void func_80147324();
void func_80146CA0();
typedef struct {
    u8 pad_0[184];
    s16 fB8;
    u8 pad_BA[0x234-0xBA];
    s32 f234;
} T;
void func_8015CCD0(T *p) {
    func_80154150(p, 20);
    p->fB8 = 0;
    func_801725E0(p);
    p->f234 = 15;
    func_80147324(0x6A7);
    func_80146CA0(p);
}

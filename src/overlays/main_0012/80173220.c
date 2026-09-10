/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147324();
void func_80019064();
void func_80171A1C();
void func_80174650();
extern s32 D_801818F8;
typedef struct { u8 pad[0xB8]; u16 b8; } T;
void func_80173220(T *p) {
    if (p->b8 & 0x4000) {
        func_80147324(0x516);
        func_80019064(&D_801818F8);
    }
    if (p->b8 & 0x8000) {
        func_80171A1C(p);
        func_80174650(p);
    }
}

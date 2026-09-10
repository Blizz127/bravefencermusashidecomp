/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80149020();
void func_801470B4();
void func_801470AC();
void func_80147A84();
void func_801473EC();
void func_80148038();
void func_80147460();
void func_801472C8();
void func_8015369C();
void func_80146CA0();
extern u16 D_800B99DA;
typedef struct { u8 pad[0xDE]; u8 uDE; } T;
void func_8015294C(T *p) {
    func_80149020(p);
    if (D_800B99DA & 1) {
        func_801470B4(p);
    } else {
        func_801470AC(p);
    }
    func_80147A84(p);
    func_801473EC(p);
    func_80148038(p, 0x18000);
    func_80147460(p);
    if (p->uDE-- == 0) {
        p->uDE = 0x10;
        func_801472C8(p);
        func_801470B4(p);
        func_8015369C(p);
        func_80146CA0(p);
    }
}

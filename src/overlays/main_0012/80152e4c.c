/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80149020();
void func_80153B58();
void func_80147A84();
void func_801473EC();
void func_80148038();
void func_80147460();
void func_801472C8();
void func_801470B4();
void func_8015369C();
void func_80146CA0();
typedef struct { u8 pad[0xDE]; u8 uDE, uDF; } T;
void func_80152E4C(T *p) {
    func_80149020(p);
    func_80153B58(p);
    func_80147A84(p);
    func_801473EC(p);
    if (p->uDF == 0) {
        func_80148038(p, 0x18000);
    } else {
        p->uDF--;
    }
    func_80147460(p);
    if (p->uDE-- == 0) {
        p->uDE = 0x10;
        func_801472C8(p);
        func_801470B4(p);
        func_8015369C(p);
        func_80146CA0(p);
    }
}

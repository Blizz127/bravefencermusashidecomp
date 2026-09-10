/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80149020();
void func_80148038();
void func_80147460();
void func_801470B4();
void func_8015369C();
void func_80146CA0();
typedef struct {
    u8 pad[0xA]; s16 uA;
    u8 padC[0xD2]; u8 uDE;
} T;
void func_80153410(T *p) {
    func_80149020(p);
    func_80148038(p, 0x18000);
    func_80147460(p);
    if (p->uA >= 0x201 || p->uDE-- == 0) {
        func_801470B4(p);
        func_8015369C(p);
        func_80146CA0(p);
    }
}

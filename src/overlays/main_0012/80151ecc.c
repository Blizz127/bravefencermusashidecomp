/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80149020();
void func_80146CA0();
void func_80172630();
typedef struct { u8 pad[0x64]; s16 u64; u8 pad66[0x78]; u8 uDE; } T;
void func_80151ECC(T *p) {
    func_80149020(p);
    p->u64 += p->uDE << 6;
    p->uDE += 5;
    if (p->u64 >= 0x1556) {
        p->uDE = 0x10;
        func_80146CA0(p);
    }
    func_80172630(p);
}

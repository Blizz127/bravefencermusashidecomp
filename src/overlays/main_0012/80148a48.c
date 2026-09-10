/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct {
    u8 pad[0xA9]; u8 uA9;
    u16 uAA;
    u8 padAC[2]; u16 uAE;
} T;

s32 func_80148A48(T *p) {
    switch (p->uA9) {
    case 0x41:
        return p->uAA & 0x2000;
    case 0x53:
    case 0x73:
        return (u8)p->uAE >= 0xC1;
    default:
        return 0;
    }
}

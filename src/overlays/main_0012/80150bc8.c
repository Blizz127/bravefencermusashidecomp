#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80146994(s32, s32, s32, s32);                      /* static */
s32 func_8014BF6C();                                /* static */
void func_80151184(s32, s32, s32);                         /* static */
s32 func_801619D0();                                /* static */
extern u16 D_800B99DA;

void func_80150BC8(s32 arg0) {
    if (func_801619D0() != 0) {
        if (D_800B99DA & 7) {
            func_80146994(0x34, arg0, 0, 0);
        }
    } else if (!(func_8014BF6C() & 0xFF)) {
        func_80151184(arg0, 0xC003, 0x10);
    }
}

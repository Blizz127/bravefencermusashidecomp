/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_80146994(s32, s32, s32, s32);                      /* static */
extern u16 D_800B99DA;

void func_80150FD8(s32 arg0) {
    if (D_800B99DA & 7) {
        func_80146994(0x34, arg0, 0, 0);
    }
}

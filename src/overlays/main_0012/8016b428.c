/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8016B428 (main_0012.s), decoded manually from
 * raw asm (0x20 bytes; m2c arg placement corrected: the jal delay
 * slot zeroes a1 while a0 still holds the incoming argument, so
 * the call is B448(arg0, 0), not B448(0); NOT verified against
 * retail; C89-gated only, promotion requires an oracle MATCH). */

extern void func_8016B448(void *arg0, s32 arg1);

void func_8016B428(void *arg0) {
    func_8016B448(arg0, 0);
}

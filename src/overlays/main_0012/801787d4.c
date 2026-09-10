/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80178840();
extern u8 D_801202A0[];
typedef struct { u16 id; u8 pad2[0xBE]; u8 uC0; u8 padC1[0x4B]; } S;
void func_801787D4(void) {
    S *s;
    s32 i;
    s = (S *)D_801202A0;
    for (i = 0; i < 0x60; i++, s++) {
        if (s->id && s->uC0) {
            func_80178840(s);
        }
    }
}

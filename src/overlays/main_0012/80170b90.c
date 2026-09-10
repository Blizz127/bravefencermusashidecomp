/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147060();
void func_80171928();
typedef struct { u8 pad[0xB8]; u16 f; } T;
void func_80170B90(T *p) {
    if (p->f & 0x8000) {
        func_80147060(p);
        func_80171928(p);
    }
}

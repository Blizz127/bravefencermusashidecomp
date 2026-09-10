/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80161C24();
void func_8014C010();
extern u16 D_800B99DA;
typedef struct {
    u8 pad[0x2C]; s32 u2C;
    u8 pad30[0x88]; u16 b8;
    u8 padBA[0xB4]; u16 u16E;
} T;
void func_80172414(T *p) {
    if (p->b8 & 0x2000) {
        func_80161C24(p, p->u16E);
    }
    if (p->u2C < (s32)0xFFF90000) {
        if ((D_800B99DA & 7) == 0) {
            func_8014C010(p, 2);
        }
    }
}

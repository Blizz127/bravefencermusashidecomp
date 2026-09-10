/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80142DB8();
s32 func_8012C0EC();
void func_80142BB4();
void func_80142C9C();
s32 func_8012BF10();
void func_8012AD44();
typedef struct { u8 pad[0x100]; s16 u100; } T;
void func_80142838(T *p) {
    if (func_80142DB8(p) == 1) {
        func_80142BB4(p, 1, 3);
    } else if (p->u100 != 0) {
        if (func_8012C0EC(p)) {
            func_80142BB4(p, 0, 3);
        }
    } else {
        func_80142C9C(p);
        if (func_8012BF10(p, 0x30)) {
            func_8012AD44(p, 2);
        }
    }
}

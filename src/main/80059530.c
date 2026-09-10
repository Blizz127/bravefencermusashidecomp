#include "psx_types.h"

typedef struct {
    u8 pad00[0x34];
    void (*callback34)(s32);
} GraphicsDispatch;

extern u8 D_80072789;
extern u8 D_8007278A;
extern char D_800740FC[];
extern void (*D_80072784)(const char *, s32);
extern GraphicsDispatch *D_80072780;
extern void func_800425E0(s32, s32);

/* Adjacent helper recovered from the unlabeled 800594CC span and verified
 * byte-exact with gcc-2.7.2-psx -O2. The state store is deliberately before
 * the call in C so retail places it in the MIPS call delay slot. */
u8 func_80059530(s32 argument) {
    u8 *state;
    u8 previous;

    state = &D_80072789;
    previous = *state;
    if (D_8007278A >= 2)
        D_80072784(D_800740FC, argument);
    if (argument != *state) {
        D_80072780->callback34(1);
        *state = argument;
        func_800425E0(2, 0);
    }
    return previous;
}

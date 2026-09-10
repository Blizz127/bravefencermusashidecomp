#include "psx_types.h"

extern s32 D_80078C80;
extern s32 D_80078C84;
extern s32 D_80078C88;
extern s32 D_80078C8C;
extern char D_800744C0[];
extern void func_8005FDD4(void *);
extern void func_8006289C(void *);
extern s32 func_8005C604(const char *);

/* Byte-exact one-time initialization range [8005FD58,8005FDD4). */
s32 func_8005FD58(s32 argument) {
    volatile s32 *state = &D_80078C80;
    if (*state != 0) {
        func_8005C604(D_800744C0);
        return 0;
    }
    *state = 1;
    D_80078C84 = 0;
    D_80078C88 = 0;
    D_80078C8C = argument;
    func_8006289C(func_8005FDD4);
    return 1;
}

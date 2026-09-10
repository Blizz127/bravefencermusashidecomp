#include "psx_types.h"

extern s32 D_80078C80;
extern void func_80042644(s32, void *);
extern void func_80061AA0(void);

/* Byte-exact state poll and dispatch [8005FD18,8005FD58). */
void func_8005FD18(void) {
    volatile s32 *state = &D_80078C80;
    while (*state != 0)
        ;
    func_80042644(7, 0);
    func_80061AA0();
}

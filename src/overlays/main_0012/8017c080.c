#include "psx_types.h"

/* Byte-exact full-range recovery [8017C080,8017C0DC), including the
 * generated split at 8017C088. No table bounds are inferred. */
extern u16 D_80115112;
extern u16 D_80115116;
extern void (*D_801827C0[])(void);
extern void func_80141C04(void);

void func_8017C080(void) {
    D_801827C0[D_80115112]();
    func_80141C04();
    D_80115116 += 1;
}

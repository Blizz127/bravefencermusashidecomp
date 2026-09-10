#include "psx_types.h"

/* Byte-exact recovery. This array view addresses the same PS1 halfword
 * as scalar views in other matching units; it is not new native storage. */
extern void func_800D24A0(s32);
extern void func_8017C120(void);
extern void func_8002AF18(void);
extern u16 D_80115112[];

void func_8017C0DC(void) {
    func_800D24A0(5);
    func_8017C120();
    func_8002AF18();
    D_80115112[0]++;
}

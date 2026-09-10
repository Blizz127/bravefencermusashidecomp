#include "psx_types.h"

/* Byte-exact recovery of [8017C120,8017C24C).
 * Addresses are PS1 words: these casts target the matching 32-bit compiler,
 * not native pointer conversion. Preserve the overlapping retail storage.
 * Branch-local configuration assignments reproduce retail scheduling. */
extern s32 D_80185AD4, D_801825A0, D_80182638;
extern s16 D_801857E8, D_801857EC, D_801857F4;
extern s16 D_80115118, D_80115126, D_8011512C;
extern u8 D_80185AE4[], D_80115138[];
extern u8 D_80115130[];
extern u32 D_80115134;
extern u32 D_801826E4[];

void func_8017C120(void) {
    s16 next, i;
    s32 index, offset;
    D_80185AD4 = 0;
    i = 0;
    do {
        D_80185AE4[i] = 0xFF;
        next = i + 1;
        i = next;
    } while (next < 8);
    D_801857E8 = 0;
    D_801857F4 = 0;
    D_80115118 = 0;
    if (D_801857EC == 0) {
        D_8011512C = 0;
        D_80182638 = D_801825A0;
    } else {
        D_8011512C = 9;
        D_80182638 = 0x1A;
    }
    i = 0;
    *(s32 *)D_80115130 = 0;
    D_80115134 = D_801826E4[D_80115126];
    do {
        index = i;
        offset = index << 5;
        next = i + 1;
        i = next;
        D_80115138[index] = *(u16 *)(offset + D_80115134);
        *(u16 *)(D_80115130 + 0x28 + index * 2) =
            *(u16 *)(offset + D_80115134 + 2);
    } while (next < 6);
}

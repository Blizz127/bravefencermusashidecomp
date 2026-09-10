#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_80029FD4();                                /* extern */
s32 func_80029FE4();                                /* extern */
s32 func_8002A26C();                                /* extern */
s32 func_8002A2B0();                                /* extern */
s32 func_8002A4B8();                                /* extern */
s32 func_8002A4FC();                                /* extern */
s32 func_8002A728();                                /* extern */
s32 func_8002A76C();                                /* extern */
s32 func_8002A998();                                /* extern */
s32 func_8002A9DC();                                /* extern */
s32 func_8002AAB4();                                /* extern */
void func_8005C540(s32, s32);                          /* extern */
s32 func_800D2CA8(s32, s32);                          /* extern */
void func_800D2D10(s32, s32, s32, s32);                    /* extern */
extern s32 D_8017F324;
extern s32 D_8017F344;
extern s32 D_8017F348;
extern s32 D_8017F34C;
extern s32 D_8017F350;
extern s32 D_8017F354;
extern s16 D_80115128;

void func_80140F00(void) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s0_5;
    s32 temp_s0_6;

    if (D_80115128 == 0) {
        temp_s0 = D_8017F324;
        func_800D2D10(func_800D2CA8(func_80029FE4() + 1, 0x18), 2, temp_s0 + 4, 1);
        func_8005C540(temp_s0 + 0xA, func_8002AAB4());
        temp_s0_2 = D_8017F344;
        func_800D2D10(func_800D2CA8(func_8002A26C() + 1, 0x18), 2, temp_s0_2 + 0x12, 1);
        func_800D2D10(func_800D2CA8(func_8002A2B0(), 0x18), 2, temp_s0_2 + 0x22, -1);
        temp_s0_3 = D_8017F348;
        func_800D2D10(func_800D2CA8(func_8002A4B8() + 1, 0x18), 2, temp_s0_3 + 0x12, 1);
        func_800D2D10(func_800D2CA8(func_8002A4FC(), 0x18), 2, temp_s0_3 + 0x22, -1);
        temp_s0_4 = D_8017F34C;
        func_800D2D10(func_800D2CA8(func_8002A998() + 1, 0x18), 2, temp_s0_4 + 0x12, 1);
        func_800D2D10(func_800D2CA8(func_8002A9DC(), 0x18), 2, temp_s0_4 + 0x22, -1);
        temp_s0_5 = D_8017F350;
        func_800D2D10(func_800D2CA8(func_8002A728() + 1, 0x18), 2, temp_s0_5 + 0x12, 1);
        func_800D2D10(func_800D2CA8(func_8002A76C(), 0x18), 2, temp_s0_5 + 0x22, -1);
        temp_s0_6 = D_8017F354;
        func_800D2D10(func_800D2CA8(func_80029FD4(), 4), 7, temp_s0_6 + 0x18, -1);
    }
}

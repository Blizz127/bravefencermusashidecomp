#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80011C10();                                  /* extern */
void func_80011E24();                                  /* extern */
void func_80015310();                                  /* extern */
void func_800285AC();                                  /* extern */
void func_8002AEF8();                                  /* extern */
void func_800CFBBC();                                  /* extern */
void func_800D0630();                                  /* extern */
void func_80128C14();                                  /* static */
void func_80129220();                                  /* static */
void func_80129C40();                                 /* static */
void func_801378F0();                                  /* static */
void func_8013C98C();                                  /* static */
void func_80144B9C();                                  /* static */
void func_80145CEC();                                  /* static */
extern s8 D_800B9A10;
extern s8 D_800B9A17;

void func_80128420(void) {
    func_80129220();
    func_801378F0();
    func_80011E24();
    func_80128C14();
    func_8002AEF8();
    func_800CFBBC();
    func_80015310();
    func_800285AC();
    D_800B9A17 = 0;
    D_800B9A10 = 0;
    func_8013C98C();
    func_80129C40(0);
    func_800D0630();
    func_80145CEC();
    func_80144B9C();
    func_80011C10();
}

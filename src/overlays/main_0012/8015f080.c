/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154150();
void func_80154A74();
void func_80146994();
void func_80149048();
void func_80156648();
void func_80149020();
void func_80146CA0();
typedef struct {
    u8 pad[0x44];
    u32 flags;
    u8 pad48[0xF6-0x48];
    s16 fF6;
    u8 padF8[0x1AA-0xF8];
    u8 f1AA;
    u8 pad1AB[0x234-0x1AB];
    s32 f234;
    s32 f238;
} T;
void func_8015F080(T *p) {
    func_80154150(p, 0x17);
    func_80154A74(p, 0x15);
    func_80146994(5, p, 7, 0);
    p->f238 = -1;
    p->f234 = 0;
    p->flags &= -2;
    func_80149048(p);
    func_80156648(p);
    p->f1AA = 8;
    func_80149020(p);
    p->fF6 = 0x19EB;
    func_80146CA0(p);
}

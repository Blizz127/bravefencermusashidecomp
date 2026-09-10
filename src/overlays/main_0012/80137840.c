/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80137840 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * 0x18 frame. Bulk initializer over s0 = a0 (offsets 0x4..0x4A):
 * bytes 0xC/0x23 = 1, halves 0x1A = 1, 0x28/0x2A = 0x1000,
 * 0x2C = 0x24, 0x2E = 3, byte 0x1F = -1; halves 0x4/0x6/0x1C/
 * 0x10/0x14/0x12/0x16/0x30/0x32/0x34/0x36/0x44/0x46/0x48/0x4A =
 * 0, bytes 0x22/0x20/0xD = 0, word 0x40 = 0 (assignments mirror
 * asm order). Then func_80139634(s0) (a0 live past store-only
 * prologue: passthrough; 0x4A zero rides the jal delay slot)
 * and func_80139DC8() (0-arg: incoming a0 never read; b0D =
 * 0 rides its delay slot). Results ignored. 39634/39DC8
 * decls inferred from
 * these single sites. Sole caller func_801377B4 ignores $v0. */

struct init_80137840 {
    u8 pad00[4];
    u16 h04;
    u16 h06;
    u8 pad08[4];
    u8 b0C;
    u8 b0D;
    u8 pad0E[2];
    u16 h10;
    u16 h12;
    u16 h14;
    u16 h16;
    u16 h18;
    u16 h1A;
    u16 h1C;
    u8 pad1E;
    s8 b1F;
    u8 b20;
    u8 pad21;
    u8 b22;
    u8 b23;
    u8 pad24[4];
    u16 h28;
    u16 h2A;
    u16 h2C;
    u16 h2E;
    u16 h30;
    u16 h32;
    u16 h34;
    u16 h36;
    u8 pad38[8];
    u32 w40;
    u16 h44;
    u16 h46;
    u16 h48;
    u16 h4A;
};

extern void func_80139634(struct init_80137840 *arg0);
extern void func_80139DC8(void);

void func_80137840(struct init_80137840 *arg0) {
    arg0->b0C = 1;
    arg0->b23 = 1;
    arg0->h1A = 1;
    arg0->h2A = 0x1000;
    arg0->h28 = 0x1000;
    arg0->h2C = 0x24;
    arg0->h2E = 3;
    arg0->h04 = 0;
    arg0->h06 = 0;
    arg0->h1C = 0;
    arg0->h10 = 0;
    arg0->h14 = 0;
    arg0->h12 = 0;
    arg0->h16 = 0;
    arg0->h30 = 0;
    arg0->h32 = 0;
    arg0->h34 = 0;
    arg0->h36 = 0;
    arg0->b22 = 0;
    arg0->b20 = 0;
    arg0->w40 = 0;
    arg0->b1F = -1;
    arg0->h44 = 0;
    arg0->h46 = 0;
    arg0->h48 = 0;
    arg0->h4A = 0;
    func_80139634(arg0);
    arg0->b0D = 0;
    func_80139DC8();
}

#include "psx_types.h"

/* Exact matched stream for the bounded native callback-initialization
 * diagnostic. The executable path stops at the first BIOS service below. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafb00010)
MUSASHI_NATIVE_MIPS_WORD(0x3c108007)
MUSASHI_NATIVE_MIPS_WORD(0x2610bafc)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0014)
MUSASHI_NATIVE_MIPS_WORD(0x96020000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1440002a)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x3c038007)
MUSASHI_NATIVE_MIPS_WORD(0x8c63cb88)
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
MUSASHI_NATIVE_MIPS_WORD(0x8c42cb8c)
MUSASHI_NATIVE_MIPS_WORD(0x3c053333)
MUSASHI_NATIVE_MIPS_WORD(0xa4400000)
MUSASHI_NATIVE_MIPS_WORD(0x94420000)
MUSASHI_NATIVE_MIPS_WORD(0x34a53333)
MUSASHI_NATIVE_MIPS_WORD(0xa4620000)
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
MUSASHI_NATIVE_MIPS_WORD(0x8c42cb90)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0xac450000)
MUSASHI_NATIVE_MIPS_WORD(0x0c010b19)
MUSASHI_NATIVE_MIPS_WORD(0x2405041a)
MUSASHI_NATIVE_MIPS_WORD(0x0c017366)
MUSASHI_NATIVE_MIPS_WORD(0x26040038)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c0109fd)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3c108007)
MUSASHI_NATIVE_MIPS_WORD(0x2610bb38)
MUSASHI_NATIVE_MIPS_WORD(0x2604fffc)
MUSASHI_NATIVE_MIPS_WORD(0x26020fdc)
MUSASHI_NATIVE_MIPS_WORD(0x0c0173be)
MUSASHI_NATIVE_MIPS_WORD(0xae020000)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x0c010b24)
MUSASHI_NATIVE_MIPS_WORD(0xa602ffc4)
MUSASHI_NATIVE_MIPS_WORD(0x3c038007)
MUSASHI_NATIVE_MIPS_WORD(0x8c63cb84)
MUSASHI_NATIVE_MIPS_WORD(0x0c010b6e)
MUSASHI_NATIVE_MIPS_WORD(0xac620014)
MUSASHI_NATIVE_MIPS_WORD(0x3c048007)
MUSASHI_NATIVE_MIPS_WORD(0x8c84cb84)
MUSASHI_NATIVE_MIPS_WORD(0x0c017394)
MUSASHI_NATIVE_MIPS_WORD(0xac820004)
MUSASHI_NATIVE_MIPS_WORD(0x0c0173c6)
MUSASHI_NATIVE_MIPS_WORD(0x2610ffc4)
MUSASHI_NATIVE_MIPS_WORD(0x02001021)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0014)
MUSASHI_NATIVE_MIPS_WORD(0x8fb00010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

/* Byte-exact C recovery of callback initialization [80042718,800427F4).
 * Guest pointer views and saved CPU context are PS1-width only, not native
 * bindings. Empty tied operands retain the observed base-register lifetime
 * without adding instructions. The guarded path includes nonlocal resume. */

typedef struct {
    u32 opaque00;
    u32 callback04;
    u8 opaque08[0xC];
    u32 callback14;
} CallbackTable;
extern CallbackTable *D_8006CB84;
extern u8 D_8006BAFC[], D_8006BB38[];
extern volatile u16 *D_8006CB88, *D_8006CB8C;
extern volatile u32 *D_8006CB90;
extern void func_80042C64(void *, s32);
extern s32 func_8005CD98(void *);
extern void func_800427F4(void);
extern void func_8005CEF8(void *);
extern u32 func_80042C90(void), func_80042DB8(void);
/* Observed incoming a0 at this BIOS call is the callback-table pointer;
 * this declaration records register flow, not inferred BIOS semantics. */
extern void func_8005CE50(CallbackTable *), func_8005CF18(void);

void *func_80042718(void) {
    u8 *state = D_8006BAFC;
    register u8 *buffer asm("s0");
    if (*(u16 *)state != 0)
        return 0;
    {
        volatile u16 *status = D_8006CB88;
        volatile u16 *mask = D_8006CB8C;
        *mask = 0;
        *status = *mask;
    }
    *D_8006CB90 = 0x33333333;
    func_80042C64(state, 0x41A);
    if (func_8005CD98(state + 0x38))
        func_800427F4();
    buffer = D_8006BB38;
    asm("" : "=r"(buffer) : "0"(buffer));
    *(u32 *)buffer = (u32)(buffer + 0xFDC);
    func_8005CEF8(buffer - 4);
    *(u16 *)(buffer - 0x3C) = 1;
    D_8006CB84->callback14 = func_80042C90();
    D_8006CB84->callback04 = func_80042DB8();
    func_8005CE50(D_8006CB84);
    func_8005CF18();
    buffer -= 0x3C;
    asm("" : "=r"(buffer) : "0"(buffer));
    return buffer;
}

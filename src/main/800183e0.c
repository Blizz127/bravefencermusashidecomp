/* Exact retail word export for [800183E0,80018450); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x24070001)
MUSASHI_NATIVE_MIPS_WORD(0x3C03800B)
MUSASHI_NATIVE_MIPS_WORD(0x2463F630)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x00610821)
MUSASHI_NATIVE_MIPS_WORD(0x8422A1A8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1440000C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x00610821)
MUSASHI_NATIVE_MIPS_WORD(0xA427A1A8)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x00610821)
MUSASHI_NATIVE_MIPS_WORD(0xAC24A1AC)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x00610821)
MUSASHI_NATIVE_MIPS_WORD(0xA020A1B5)
MUSASHI_NATIVE_MIPS_WORD(0x08006112)
MUSASHI_NATIVE_MIPS_WORD(0x24060001)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x28A20020)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFEC)
MUSASHI_NATIVE_MIPS_WORD(0x24630010)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00C01021)
#else
/* Retail [800183E0,80018450): reserve the first free entry in a 32-slot queue.
 * GCC 2.7.2 / ASPSX 2.56 -O2 -G0, --link-base 0x800183E0: 28/28 words.
 * Empty compiler constraints preserve initialization ordering and the retail
 * base-relative access shape; they emit no instructions. Field names describe
 * the observed accesses, not recovered original source identifiers.
 */
typedef struct QueueEntry {
    short active;
    short unknown;
    unsigned int value;
    unsigned char tail[5];
    unsigned char state;
    unsigned char padding[2];
} QueueEntry;
typedef struct State {
    unsigned char prefix[0xA1A8];
    QueueEntry entries[32];
} State;
extern State D_800AF630;
int func_800183E0(unsigned int value)
{
    int result = 0;
    int i = 0;
    int one = 1;
    State *base;
    __asm__("" : : "r"(result), "r"(i), "r"(one));
    base = &D_800AF630;
    for (; i < 32; ++i, base = (State *)((unsigned char *)base + 16)) {
        __asm__("" : "=r"(base) : "0"(base));
        if (base->entries[0].active == 0) {
            base->entries[0].active = one;
            base->entries[0].value = value;
            base->entries[0].state = 0;
            result = 1;
            break;
        }
    }
    return result;
}

#endif

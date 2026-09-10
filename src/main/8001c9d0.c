/* Exact retail [8001C9D0,8001CA1C). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24021000)
MUSASHI_NATIVE_MIPS_WORD(0xA482001C)
MUSASHI_NATIVE_MIPS_WORD(0xA482001A)
MUSASHI_NATIVE_MIPS_WORD(0xA4820018)
MUSASHI_NATIVE_MIPS_WORD(0x240200C8)
MUSASHI_NATIVE_MIPS_WORD(0xA4800014)
MUSASHI_NATIVE_MIPS_WORD(0xA4800012)
MUSASHI_NATIVE_MIPS_WORD(0xA4800010)
MUSASHI_NATIVE_MIPS_WORD(0xA480000C)
MUSASHI_NATIVE_MIPS_WORD(0xA480000A)
MUSASHI_NATIVE_MIPS_WORD(0xA4800008)
MUSASHI_NATIVE_MIPS_WORD(0xAC800004)
MUSASHI_NATIVE_MIPS_WORD(0xAC800020)
MUSASHI_NATIVE_MIPS_WORD(0xA4820028)
MUSASHI_NATIVE_MIPS_WORD(0xA482002A)
MUSASHI_NATIVE_MIPS_WORD(0xA480002C)
MUSASHI_NATIVE_MIPS_WORD(0xA480002E)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC800080)
#else
/* Retail [8001C9D0,8001CA1C): initialize object transform and control fields. */
void func_8001C9D0(unsigned char *object)
{
    *(short *)(object+0x1C) = 0x1000;
    *(short *)(object+0x1A) = 0x1000;
    *(short *)(object+0x18) = 0x1000;
    *(short *)(object+0x14) = 0;
    *(short *)(object+0x12) = 0;
    *(short *)(object+0x10) = 0;
    *(short *)(object+0x0C) = 0;
    *(short *)(object+0x0A) = 0;
    *(short *)(object+0x08) = 0;
    *(int *)(object+0x04) = 0;
    *(int *)(object+0x20) = 0;
    *(short *)(object+0x28) = 200;
    *(short *)(object+0x2A) = 200;
    *(short *)(object+0x2C) = 0;
    *(short *)(object+0x2E) = 0;
    *(int *)(object+0x80) = 0;
}

#endif

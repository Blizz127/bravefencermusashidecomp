/* Complete retail export [80148800,8014880C). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x948200AC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
unsigned short func_80148800(unsigned char *state)
{
    return *(unsigned short *)(state+0xAC);
}
#endif

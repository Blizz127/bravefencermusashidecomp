/* Complete SC02 state increment; independently matched ordinary C. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x94820002)
MUSASHI_NATIVE_MIPS_WORD(0xA4800034)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4820002)
#else
/* Complete SC02 member 31 [8012AD50,8012AD64), 5 words. */
typedef struct Object { unsigned short id, state; unsigned char pad[0x30]; unsigned short flag; } Object;
void func_8012AD50(Object *object)
{
    object->flag = 0;
    object->state++;
}
#endif

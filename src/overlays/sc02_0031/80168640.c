/* SC02.CD FILE_031 / ov_SC02_031 retail span [80168640,80168664).
 * Offset 0x404E8 at overlay base 80128158. SHA256(span)=7fc72c9f69cadad20c86c0b43fca539e0f0acf80746908ba9300f5f4f7c25a46.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80168640.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020020)
MUSASHI_NATIVE_MIPS_WORD(0xAC82001C)
MUSASHI_NATIVE_MIPS_WORD(0x94820002)
MUSASHI_NATIVE_MIPS_WORD(0x24030080)
MUSASHI_NATIVE_MIPS_WORD(0xA4800012)
MUSASHI_NATIVE_MIPS_WORD(0xA4830010)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4820002)
#else
#include "psx_types.h"
typedef struct { u8 pad[2]; s16 unk2; u8 pad4[0xC]; s16 unk10, unk12; u8 pad14[8]; s32 unk1C; } T;
void func_80168640(T *p) {
    p->unk1C = 0x20;
    p->unk12 = 0;
    p->unk10 = 0x80;
    p->unk2++;
}
#endif

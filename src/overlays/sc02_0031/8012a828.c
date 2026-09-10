/* Complete SC02 retail span [8012A828,8012A860).
 * Script attach helper (dep of 848 cluster).
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x94820072)
MUSASHI_NATIVE_MIPS_WORD(0xAC850090)
MUSASHI_NATIVE_MIPS_WORD(0xAC800094)
MUSASHI_NATIVE_MIPS_WORD(0xAC80009C)
MUSASHI_NATIVE_MIPS_WORD(0xA480009A)
MUSASHI_NATIVE_MIPS_WORD(0x3042F9FF)
MUSASHI_NATIVE_MIPS_WORD(0x0C04AAAB)
MUSASHI_NATIVE_MIPS_WORD(0xA4820072)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* From vendor shared ov (types reproduce bytes). */
/* func_8012A828 — shared body (overlay slot 0x80128158, h_exact 5f61e157). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012AAAC();
void func_8012A828(s32 a0, void * a1)
{
    *(s32 *)((u8 *)a0 + 0x90) = a1;
    *(s32 *)((u8 *)a0 + 0x94) = 0;
    *(s32 *)((u8 *)a0 + 0x9C) = 0;
    *(s16 *)((u8 *)a0 + 0x9A) = 0;
    *(u16 *)((u8 *)a0 + 0x72) = *(u16 *)((u8 *)a0 + 0x72) & 0xF9FF;
    func_8012AAAC();
}
#endif

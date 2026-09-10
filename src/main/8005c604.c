#include "psx_types.h"

/* Byte-exact recovery of the PS1 varargs home-area wrapper
 * [8005C604,8005C640). The caller-area stores are intentional: retail's
 * formatter consumes the words at SP+1C, including the format word at SP+18.
 * This source is oracle/decompilation code and is not a native binding. */
extern s32 func_8005C640(s32, const char *, s32 *);

/* This is the exact 15-word instruction stream emitted for this matched
 * function. It is retained beside the equivalent C so the native MIPS seam
 * can execute the same audited implementation without reading retail media or
 * creating a host-varargs companion. The macro is deliberately undefined in
 * retail and native C compilation. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0x00801021)
MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0xafa5001c)
MUSASHI_NATIVE_MIPS_WORD(0x00402821)
MUSASHI_NATIVE_MIPS_WORD(0xafa60020)
MUSASHI_NATIVE_MIPS_WORD(0x27a6001c)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0xafa20018)
MUSASHI_NATIVE_MIPS_WORD(0x0c017190)
MUSASHI_NATIVE_MIPS_WORD(0xafa70024)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

s32 func_8005C604(const char *format, s32 arg1, s32 arg2, s32 arg3) {
    s32 *arguments = &arg1;
    arguments[-1] = (s32)format;
    arguments[1] = arg2;
    arguments[2] = arg3;
    return func_8005C640(1, format, arguments);
}

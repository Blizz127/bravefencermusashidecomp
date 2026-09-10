#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */
#ifdef MUSASHI_NATIVE_CALLBACK_HANDLER
#include "musashi_boot_memory.h"
int musashi_boot_call_8001096c(MusashiBootMemory *memory,
    MusashiGuestCallbackExecutor execute, void *userdata) {
    if (!memory) return 0;
    if (!execute || !execute(userdata, memory, 0x8002cdd8u)) return 0;
    return 1;
}
#else
void func_8002CDD8();                                  /* static */

void func_8001096C(void) {
    func_8002CDD8();
}
#endif

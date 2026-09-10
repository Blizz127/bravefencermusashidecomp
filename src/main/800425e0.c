#include "psx_types.h"

/* Initialization fills the slot at runtime; retaining
 * indirection is required even though its initial installed target is known.
 * The second argument carries a 32-bit callback address, not a host pointer. */
#ifdef MUSASHI_NATIVE_CALLBACK_DISPATCH
#include "musashi_callback_registration.h"
#define LOAD_TARGET() u32 table, target; \
    if (!musashi_boot_read32(memory, 0x8006cb84u, &table) || \
        !musashi_boot_read32(memory, table + 4u, &target)) return 0
#define INVOKE(target, channel, callback) \
    ((target) == 0x80042f8cu && \
     musashi_boot_call_80042f8c(memory, device, channel, callback, previous))
int musashi_boot_call_800425e0(MusashiBootMemory *memory,
    const MusashiDmaCallbackRegistrationDevice *device, s32 channel,
    u32 callback, u32 *previous) {
#else
typedef s32 (*DmaDispatch)(s32, s32);
typedef struct {
    u32 opaque00;
    DmaDispatch dispatch;
} DispatchView;
extern DispatchView *D_8006CB84;
#define LOAD_TARGET() DmaDispatch target = D_8006CB84->dispatch
#define INVOKE(target, channel, callback) target(channel, callback)
s32 func_800425E0(s32 channel, s32 callback) {
#endif
    LOAD_TARGET();
    return INVOKE(target, channel, callback);
}
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
/* Retail word export for [800425E0,80042610); EXE-verified. */
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
MUSASHI_NATIVE_MIPS_WORD(0x8c42cb84)
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x8c420004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040f809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

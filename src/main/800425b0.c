/* Byte-exact table dispatch, with guest-width views for the native binding. */
#include "psx_types.h"
#ifdef MUSASHI_NATIVE_CALLBACK_DISPATCH
#include "musashi_callback_registration.h"
#define LOAD_TARGET() u32 table, target; \
    if (!musashi_boot_read32(memory, 0x8006cb84u, &table) || \
        !musashi_boot_read32(memory, table + 8u, &target)) return 0
#define INVOKE(target, index, callback) \
    ((target) == 0x800429dcu && \
     musashi_boot_call_800429dc(memory, device, index, callback, previous))
int musashi_boot_call_800425b0(MusashiBootMemory *memory,
    const MusashiCallbackRegistrationDevice *device, s32 index,
    u32 callback, u32 *previous) {
#else
typedef s32 (*RegisterCallback)(s32, void (*)(void));
typedef struct {
    u32 opaque[2];
    RegisterCallback register_callback;
} CallbackTable;
extern CallbackTable *D_8006CB84;
#define LOAD_TARGET() RegisterCallback target = D_8006CB84->register_callback
#define INVOKE(target, index, callback) target(index, callback)
s32 func_800425B0(s32 index, void (*callback)(void)) {
#endif
    LOAD_TARGET();
    return INVOKE(target, index, callback);
}

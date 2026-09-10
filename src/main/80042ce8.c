/* Shared retail handler; native slot values remain guest address words. */
#include "psx_types.h"
#ifdef MUSASHI_NATIVE_CALLBACK_HANDLER
#include "musashi_boot_memory.h"
typedef u32 Callback;
typedef u32 CallbackSlot;
#define SLOTS 0x8006cb98u
#define SLOT_STRIDE 4u
#define INCREMENT_TICK() do { \
    u32 tick; \
    if (!musashi_boot_read32(memory, 0x8006cbb8u, &tick) || \
        !musashi_boot_write32(memory, 0x8006cbb8u, tick + 1u)) return 0; \
} while (0)
#define READ_CALLBACK(slot) Callback callback; \
    if (!musashi_boot_read32(memory, slot, &callback)) return 0
#define EXECUTE_CALLBACK(callback) do { \
    if (!execute || !execute(userdata, memory, callback)) return 0; \
} while (0)
#define COMPLETE() return 1
int musashi_boot_call_80042ce8(MusashiBootMemory *memory,
    MusashiGuestCallbackExecutor execute, void *userdata) {
#else
typedef void (*Callback)(void);
typedef Callback *CallbackSlot;
extern Callback D_8006CB98[];
extern volatile u32 D_8006CBB8;
#define SLOTS D_8006CB98
#define SLOT_STRIDE 1
#define INCREMENT_TICK() D_8006CBB8++
#define READ_CALLBACK(slot) Callback callback = *slot
#define EXECUTE_CALLBACK(callback) callback()
#define COMPLETE() return
void func_80042CE8(void) {
#endif
    s32 index = 0;
    CallbackSlot slot = SLOTS;
    INCREMENT_TICK();
    do {
        READ_CALLBACK(slot);
        if (callback)
            EXECUTE_CALLBACK(callback);
        index++;
        slot += SLOT_STRIDE;
    } while (index < 8);
    COMPLETE();
}

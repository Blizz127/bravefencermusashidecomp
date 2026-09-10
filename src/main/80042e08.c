#include "psx_types.h"

/* Byte-exact PS1 handler. Register writes are bus values; ordinary host
 * memory does not supply the device's acknowledgment semantics. */
#ifdef MUSASHI_NATIVE_DMA_IRQ_HANDLER
#include "musashi_callback_registration.h"
#define READ_CONTROL(flags) do { \
    if (!device->read32(device->userdata, control, &(flags))) return 0; \
} while (0)
#define WRITE_CONTROL(flags) do { \
    if (!device->write32(device->userdata, control, flags)) return 0; \
} while (0)
#define CALLBACK_LOAD() do { \
    if (!musashi_boot_read32(memory, 0x8006cbc4u + (u32)channel * 4u, &callback)) \
        return 0; \
} while (0)
#define CALLBACK_CALL() do { \
    if (!execute || !execute(userdata, memory, callback)) return 0; \
} while (0)

int musashi_boot_call_80042e08(MusashiBootMemory *memory,
    const MusashiDmaCallbackRegistrationDevice *device,
    MusashiGuestCallbackExecutor execute, void *userdata) {
    u32 control, pending, flags, callback;
    s32 channel;
    if (!memory || !device || !device->read32 || !device->write32) return 0;
    if (!musashi_boot_read32(memory, 0x8006cbc0u, &control) || (control & 3u))
        return 0;
#else
typedef void (*Callback)(void);
extern Callback D_8006CBC4[];
extern volatile u32 *D_8006CBC0, *D_8006CBE4;
extern char D_80073590[], D_800735AC[];
extern s32 func_8005C604(const char *, ...);
#define READ_CONTROL(flags) ((flags) = *D_8006CBC0)
#define WRITE_CONTROL(flags) (*D_8006CBC0 = (flags))

void func_80042E08(void) {
    s32 channel;
    u32 pending;
#endif
#ifdef MUSASHI_NATIVE_DMA_IRQ_HANDLER
    READ_CONTROL(flags);
    pending = (flags >> 24) & 0x7F;
#else
    pending = (*D_8006CBC0 >> 24) & 0x7F;
#endif
    while (pending != 0) {
        channel = 0;
        while (pending != 0 && channel < 7) {
            if (pending & 1) {
#ifdef MUSASHI_NATIVE_DMA_IRQ_HANDLER
                READ_CONTROL(flags);
                WRITE_CONTROL(flags & ((1u << (channel + 24)) | 0xFFFFFFu));
                CALLBACK_LOAD();
                if (callback)
                    CALLBACK_CALL();
#else
                *D_8006CBC0 &= (1 << (channel + 24)) | 0xFFFFFF;
                if (D_8006CBC4[channel] != 0) {
                    D_8006CBC4[channel]();
                }
#endif
            }
            channel++;
            pending >>= 1;
        }
#ifdef MUSASHI_NATIVE_DMA_IRQ_HANDLER
        READ_CONTROL(flags);
        pending = (flags >> 24) & 0x7F;
#else
        pending = (*D_8006CBC0 >> 24) & 0x7F;
#endif
    }
#ifdef MUSASHI_NATIVE_DMA_IRQ_HANDLER
    READ_CONTROL(flags);
    if ((flags & 0xFF000000u) == 0x80000000u || (flags & 0x8000u) != 0)
        return 0;
    return 1;
#else
    if ((*D_8006CBC0 & 0xFF000000) == 0x80000000 ||
        (*D_8006CBC0 & 0x8000) != 0) {
        func_8005C604(D_80073590, *D_8006CBC0);
        channel = 0;
        do {
            func_8005C604(D_800735AC, channel, D_8006CBE4[channel * 4]);
            channel++;
        } while (channel < 7);
    }
#endif
}

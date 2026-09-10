#include "musashi_boot_memory.h"

extern int32_t func_8005BD7C_native(int32_t mode,
                                    MusashiBootMemory *memory,
                                    const MusashiGpuDevice *device);

int musashi_boot_call_8005bd7c(MusashiBootMemory *memory,
                               const MusashiGpuDevice *device,
                               int32_t mode, int32_t *result) {
    if (!memory || !device || !device->read16 || !device->write16 ||
        !device->read32 || !device->write32 || !result ||
        !musashi_boot_ram_span(memory, 0x80078874u, 0x100u) ||
        !musashi_boot_ram_span(memory, 0x800c5510u, 0x1800u))
        return 0;
    *result = func_8005BD7C_native(mode, memory, device);
    return 1;
}

#include "musashi_boot_memory.h"

/* Compiled from src/main/8005c1c0.c, with only the observed GPU MMIO
 * operations supplied by the platform adapter. Keeping this boundary in its
 * own translation unit leaves existing memory-only consumers linkable. */
extern int32_t func_8005C1C0_native(int32_t mode,
                                    MusashiBootMemory *memory,
                                    const MusashiGpuDevice *device);

int musashi_boot_call_8005c1c0(MusashiBootMemory *memory,
                               const MusashiGpuDevice *device,
                               int32_t mode, int32_t *result) {
    if (!memory || !device || !device->read32 || !device->write32 || !result)
        return 0;
    *result = func_8005C1C0_native(mode, memory, device);
    return 1;
}

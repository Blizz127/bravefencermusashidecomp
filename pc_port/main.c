#include <stdio.h>

#include "musashi_port.h"

int main(void) {
    static const mus_u8 probe[4] = {0x12, 0x34, 0x56, 0x78};
    MusashiRuntimeState state;
    mus_u32 decoded = 0;

    musashi_port_init(&state);
    if (state.frame_counter != 0 || state.pad_state != 0) {
        fputs("musashi_pc_smoke: runtime reset failed\n", stderr);
        return 1;
    }
    if (!musashi_port_decode_probe(probe, &decoded) || decoded != 0x78563412u) {
        fputs("musashi_pc_smoke: little-endian probe failed\n", stderr);
        return 1;
    }

    printf("musashi_pc_smoke: platform=%s frame=%u pad=%u le32=0x%08x\n",
           musashi_port_platform_name(),
           (unsigned)state.frame_counter,
           (unsigned)state.pad_state,
           (unsigned)decoded);
    return 0;
}

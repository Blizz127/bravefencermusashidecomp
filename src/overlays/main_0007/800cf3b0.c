/* Matched functions from MAIN.CD member 0007.
 *
 * The overlay loads at 0x800CEDF8; see config/overlay_main_0007.yaml for how
 * that address was derived from the member's own bytes.
 *
 * The filename is provisional and names the address the function starts at.
 */

#include "psx_types.h"

/* Both references live outside this overlay and are resolved at link time from
 * their splat names, which carry their addresses. */
extern s32 func_800149E0(s32 port);
extern s16 D_800B99E6;

/* Two-port input check at vram 0x800CF3B0.
 *
 * Reads both ports, tests one bit across the pair, and records that it was
 * seen before reporting it. The first read is held across the second call,
 * which is why it occupies a saved register.
 *
 * Signatures and types here are the loosest that reproduce the bytes; they are
 * not evidence of the original declaration.
 */
s32 func_800CF3B0(void) {
    s32 first;

    /* Written with the positive test rather than an early-out on the negative.
     * Inverting it emits beqz where retail has bnez, and swaps the order of the
     * two return paths. */
    first = func_800149E0(0);
    if ((first | func_800149E0(1)) & 0x800) {
        D_800B99E6 = 1;
        return 1;
    }
    return 0;
}

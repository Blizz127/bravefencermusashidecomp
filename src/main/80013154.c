/* Matched leaf functions from the main executable's first region.
 *
 * The filename is provisional and names the address the file starts at; it is
 * renamed once a real translation-unit boundary is identified.
 *
 * Types come from include/psx_types.h, which build_candidate.py places on the
 * search path by default.
 */

#include "psx_types.h"

/* Clamped step from one value toward another, at vram 0x80013154.
 *
 * Returns how far to move from arg0 toward arg1 given step size arg2, never
 * overshooting: when a full step would pass the target, the exact remaining
 * distance is returned instead. The step is negated when the target is below
 * the current value, so the caller passes an unsigned magnitude.
 *
 * The result is computed as a 16-bit quantity and widened on return, which is
 * why the comparisons are made on the truncated intermediate rather than on
 * the full 32-bit sum.
 *
 * Signatures and types here are the loosest that reproduce the bytes; they are
 * not evidence of the original declaration.
 */
s32 func_80013154(s16 arg0, s16 arg1, s32 arg2) {
    s32 step;
    s32 descending;
    s16 current;
    s16 next;
    s16 result;

    /* Both the step and the current value are copied before the early exit.
     * Collapsing either into its argument drops a register move and comes out
     * short of retail. */
    step = arg2;
    current = arg0;
    if (current == arg1) {
        return 0;
    }

    descending = arg1 < current;
    next = current + step;
    if (descending != 0) {
        step = -arg2;
        next = current + step;
    }

    if ((next >= arg1) && (descending == 0)) {
        result = arg1 - current;
    } else {
        result = step;
        if (arg1 >= next) {
            if (current >= arg1) {
                result = arg1 - current;
            } else {
                result = step;
            }
        }
    }
    return result;
}

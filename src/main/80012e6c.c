/* Matched leaf functions from the main executable's first region.
 *
 * The filename is provisional and names the address the file starts at, as in
 * src/main/80012ab0.c; it is renamed once a real translation-unit boundary is
 * identified.
 *
 * Types are declared locally rather than included. The Psy-Q chain runs cpp
 * with -nostdinc, so src/shared/types.h is unusable here: it pulls in stdint.h.
 * Move these to a shared decomp header once a second file needs them.
 */

typedef short s16;
typedef int s32;

/* Angle delta with optional interpolation, at vram 0x80012E6C.
 *
 * Angles are 12-bit: 0x1000 is a full turn and 0x800 a half turn, so the raw
 * difference is wrapped into (-0x800, 0x800] to take the short way round.
 *
 * When arg4 points at zero, or the divisor is zero, the wrapped delta is
 * returned directly. Otherwise the delta is scaled by arg3/arg2, and a result
 * that truncates to zero is forced to +/-1 so a caller stepping by this value
 * still converges instead of stalling. Note the sign for that step comes from
 * the *unwrapped* delta.
 *
 * Signatures and types here are the loosest that reproduce the bytes; they are
 * not evidence of the original declaration.
 */
s16 func_80012E6C(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 *arg4) {
    s16 delta;
    s16 plain;
    s16 scaled_in;
    s16 scaled;

    /* The two wrap paths keep their own copy of the delta rather than sharing
     * one. Collapsing them into a single variable drops two register moves and
     * comes out two instructions short of retail. */
    delta = arg1 - arg0;
    scaled_in = delta;
    plain = scaled_in;

    if ((*arg4 == 0) || (arg2 == 0)) {
        if (delta >= 0x801) {
            plain = delta - 0x1000;
        }
        if (plain < -0x800) {
            plain += 0x1000;
        }
        return plain;
    }

    if (delta >= 0x801) {
        scaled_in = delta - 0x1000;
    }
    if (scaled_in < -0x800) {
        scaled_in += 0x1000;
    }

    scaled = (s16) ((s32) (scaled_in * arg3) / arg2);
    if (scaled == 0) {
        scaled = -1;
        if (delta > 0) {
            scaled = 1;
        }
    }
    return scaled;
}

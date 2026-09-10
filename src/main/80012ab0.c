/* Matched leaf functions from the main executable's first region.
 *
 * The filename is provisional. splat's trailing-nop analysis suggests original
 * translation-unit seams at file offsets 0x42C60 and 0x5E4F0, which is not
 * enough to recover real source filenames, so files are named for the address
 * they start at and renamed once a boundary is actually identified.
 *
 * Every function here is byte-verified against retail.
 * Cross-checked against vendor/bfm-decomp/src/800.c (Druthulu); this
 * house-style body is preferred over the vendor TU dump form. Do not add a function
 * to this file until tools/match_function.py reports a match for it.
 */

/* Verified: 3/3 words at vram 0x80012AB0.
 *
 * The parameter and return types are the loosest that reproduce the bytes and
 * are not evidence of the original signature: subu and andi are width-agnostic
 * here, so a narrower type would emit the same code. Refine if a caller ever
 * pins the width.
 */
int func_80012AB0(int a, int b) {
    return (a - b) & 0xFFF;
}

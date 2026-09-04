/* Matched functions from MAIN.CD member 0012, the game's main code overlay.
 *
 * The member is a PAC container: its code chunk begins at file offset 0x28000
 * and loads at 0x80128158. See config/overlay_main_0012.yaml for the evidence.
 *
 * The filename is provisional and names the address the function starts at.
 */

#include "psx_types.h"

/* Word setter at vram 0x8012BF4C.
 *
 * Stores its second argument at byte offset 0x1C of the structure its first
 * argument points at. Indexing a word pointer by 7 reaches that offset without
 * needing the structure declared, which is not yet known.
 *
 * Signatures and types here are the loosest that reproduce the bytes; they are
 * not evidence of the original declaration.
 */
void func_8012BF4C(s32 *object, s32 value) {
    object[7] = value;
}

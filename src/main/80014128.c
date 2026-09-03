/* Matched leaf functions from the main executable's first region.
 *
 * The filename is provisional and names the address the file starts at; it is
 * renamed once a real translation-unit boundary is identified.
 */

#include "psx_types.h"

/* Forward declaration only. The callee lives elsewhere in the executable, so
 * this reference is undefined in the compiled object and is resolved at link
 * time from its splat name, which carries its address. */
extern void func_80048FBC(void);

/* Non-leaf wrapper at vram 0x80014128.
 *
 * Its only purpose in this repository is to prove the link step: the call is a
 * relocation, so bytes taken straight from the object would be meaningless and
 * only become comparable with retail after linking.
 *
 * Signatures and types here are the loosest that reproduce the bytes; they are
 * not evidence of the original declaration.
 */
void func_80014128(void) {
    func_80048FBC();
}

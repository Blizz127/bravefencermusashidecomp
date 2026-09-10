/* Retail startup stack-switch fragment: 800105EC..80010610,
 * 80010614..80010638 and 8001071C..80010740. Mixed assembly evidence;
 * not a pure-C function match. Native hosting needs a different boundary.
 *
 * The saved SP cell at 1F8003FC is shared: this is not a reentrant helper.
 * Callees must return with SP balanced and obey the saved-register ABI.
 * Tab-separated .set directives are required by the pinned maspsx parser.
 */
#ifndef MUSASHI_RETAIL_SCRATCH_CALL_H
#define MUSASHI_RETAIL_SCRATCH_CALL_H
#if !defined(__mips__) && !defined(mips)
#error "Retail scratch-stack calls require the PS1 MIPS target"
#endif

#define SCRATCH_CALL(target) __asm__ volatile ( \
    ".set\tnoreorder\n\t" \
    "lui $6,0x1f80\n\t" \
    "ori $6,$6,0x3fc\n\t" \
    "addu $8,$6,$0\n\t" \
    "sw $29,0($8)\n\t" \
    "addiu $8,$8,-4\n\t" \
    "addu $29,$8,$0\n\t" \
    "jal " #target "\n\t" \
    "nop\n\t" \
    "addiu $29,$29,4\n\t" \
    "lw $29,0($29)\n\t" \
    ".set\treorder\n\t" \
    : : : "$2", "$3", "$4", "$5", "$6", "$7", \
            "$8", "$9", "$10", "$11", "$12", "$13", \
            "$14", "$15", "$24", "$25", "$31", "hi", "lo", "memory")

#endif


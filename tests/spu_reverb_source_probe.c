/* Synthetic source fixture, NOT native cold-boot or captured-state proof.
 * Reuse the explicit EXE/CPU/IRQ-slot/PCM adapters, then execute the actual
 * two initializers and common attributes before tracing the reverb prefix.
 * No post-initialization allocation flags or reverb record are supplied. */
#define main startup_fixture_main
#include "spu_startup_source_probe.c"
#undef main

typedef struct ReverbWrite {
    uint32_t pc, address;
    uint16_t value;
    uint64_t cycle;
} ReverbWrite;
static ReverbWrite trace[40];
static unsigned trace_count, stage_dma_writes, list_checks;
static MusashiDmaController saved_dma;
static MusashiBiosEventTable saved_events;
static uint64_t stage_start;
static unsigned saved_opens, saved_enables, saved_enters, saved_exits;
static MusashiSpuReverbSnapshot prior_reverb;
static uint8_t cleared_ram[65536];

static int trace_write(void *u,uint32_t address,uint16_t value) {
    assert(trace_count<40);
    if(!musashi_spu_cd_audio_write16(((Fixture *)u)->audio,address,value)) return 0;
    trace[trace_count++]=(ReverbWrite){f.cpu.pc,address,value,f.cycles};
    return 1;
}
static void trace_dma_write(void *u,uint32_t address,uint32_t value) {
    ++stage_dma_writes; dma_write(u,address,value);
}
static MusashiSpuCdAudioSnapshot snapshot(void) {
    MusashiSpuCdAudioSnapshot s;
    assert(musashi_spu_cd_audio_snapshot(f.audio,&s)); return s;
}
static int reverb_run(uint32_t target) {
    unsigned budget;
    for(budget=0;budget<10000;++budget) {
        if(f.cpu.pc==target) return 1;
        if(f.cpu.pc==0x8003b408) ++list_checks;
        if(!formatter_step(&f.memory,&f.cpu)) {
            fprintf(stderr,"REVERB_REFUSED pc=%08x ra=%08x writes=%u cycles=%llu fault=%d\n",
                f.cpu.pc,f.cpu.r[31],trace_count,(unsigned long long)f.cycles,snapshot().faulted);
            return 0;
        }
    }
    return 0;
}
static void prepare(void) {
    init();
    /* Actual source creates B0F4=FFFE, B544=0, event and common record.
     * The second initializer publishes B5B0=762D0 through3FE68->4014C.
     * Its first40001010 record is a free/terminal entry;3B3D0 must inspect it.
     * The synthetic stack and IRQ prerequisites are solely those documented
     * in spu_startup_source_probe.c. This CPU remains intact throughout. */
    if(!run_to(0x8002c974)) {
        fprintf(stderr,"reverb setup refused pc=%08x cycles=%llu\n",f.cpu.pc,
            (unsigned long long)f.cycles); abort();
    }
    assert(word(0x8006b0f4)==0xfffe && word(0x8006b5b0)==0x800762d0);
    assert(word(0x800762d0)==0x40001010 && word(0x800762d4)==0x7eff0);
    assert(word(0x8006b544)==0 && word(0x8006b574)==3);
    assert(word(0x800a4ea4)==0x23cf && snapshot().control==0xc001);
    assert(f.cpu.r[29]==0x801fefe0 && word(0x801feff8)==0x12345678);
    assert(snapshot().manual_halfwords==16);
    assert(snapshot().bootstrap_halfwords==32768);
    assert(musashi_spu_cd_audio_reverb_snapshot(f.audio,&prior_reverb));
    assert(prior_reverb.base==0xfffe && !prior_reverb.enabled);
    assert(musashi_spu_cd_audio_copy_ram(f.audio,0x70000,cleared_ram,sizeof(cleared_ram)));
    {
        unsigned i; uint8_t untouched[2]={0x5a,0xa5};
        for(i=0;i<sizeof(cleared_ram);++i) assert(cleared_ram[i]==0);
        assert(!musashi_spu_cd_audio_copy_ram(f.audio,0x6fffe,untouched,sizeof(untouched)));
        assert(untouched[0]==0x5a && untouched[1]==0xa5);
    }
    memset(trace,0,sizeof(trace)); trace_count=stage_dma_writes=list_checks=0;
    saved_dma=f.dma; saved_events=f.kernel.events;
    saved_opens=f.opens; saved_enables=f.enables;
    saved_enters=f.enters; saved_exits=f.exits;
    stage_start=f.cycles;
    f.spu.write16=trace_write; f.callbacks.write32=trace_dma_write;
}
static void no_dma_or_bios(void) {
    assert(stage_dma_writes==0 && !memcmp(&saved_dma,&f.dma,sizeof(saved_dma)));
    assert(!memcmp(&saved_events,&f.kernel.events,sizeof(saved_events)));
    assert(f.opens==saved_opens && f.enables==saved_enables);
    assert(f.enters==saved_enters && f.exits==saved_exits);
    assert(snapshot().manual_halfwords==16);
}
static void coefficient_writes(void) {
    static const uint16_t expected[32]={
        0x00e3,0x00a9,0x6f60,0x4fa8,0xbce0,0x4510,0xbef0,0xa680,
        0x5680,0x52c0,0x0dfb,0x0b58,0x0d09,0x0a3c,0x0bd9,0x0973,
        0x0b59,0x08da,0x08d9,0x05e9,0x07ec,0x04b0,0x06ef,0x03d2,
        0x05ea,0x031d,0x031c,0x0238,0x0154,0x00aa,0x8000,0x8000};
    unsigned i;
    assert(trace_count>=34);
    assert(trace[0].address==0x1f801d84 && trace[0].value==0);
    assert(trace[1].address==0x1f801d86 && trace[1].value==0);
    for(i=0;i<32;++i) {
        uint16_t raw;
        assert(musashi_boot_read16(&f.memory,0x8006b718+2*i,&raw));
        assert(raw==expected[i]);
        assert(trace[i+2].address==0x1f801dc0+2*i && trace[i+2].value==raw);
        assert(trace[i+2].cycle>trace[i+1].cycle);
    }
}
static void success(void) {
    unsigned i;
    prepare();
    assert(reverb_run(0x8002c98c));
    assert(word(0x8006b0f0)==1 && word(0x8006b0ec)==1);
    assert(word(0x8006b0fc)==4 && word(0x8006b0f4)==0xf204);
    assert(word(0x800a4ecc)==1 && word(0x800a4ed0)==4 && word(0x800a4ed4)==0);
    assert(f.cpu.r[2]==1 && f.cpu.r[31]==0x8002c98c);
    assert(f.cpu.r[29]==0x801fefe0 && word(0x801feff8)==0x12345678);
    assert(trace_count==36 && list_checks==2); coefficient_writes();
    assert(trace[34].address==0x1f801da2 && trace[34].value==0xf204);
    assert(trace[35].address==0x1f801daa && trace[35].value==0xc081);
    assert(trace[35].pc==0x8003b330 && snapshot().control==0xc081);
    assert(snapshot().cycle==f.cycles && f.cycles>stage_start && !snapshot().faulted);
    no_dma_or_bios();
    for(i=0;i<trace_count;++i) printf("REVERB_WRITE pc=%08x address=%08x value=%04x cycle=%llu\n",
        trace[i].pc,trace[i].address,trace[i].value,(unsigned long long)trace[i].cycle);
    {
        MusashiSpuReverbSnapshot before,after;
        MusashiSpuCdAudioSnapshot audio=snapshot();
        uint64_t source_end=f.cycles;
        assert(musashi_spu_cd_audio_reverb_snapshot(f.audio,&before));
        assert(before.base==0xf204 && before.enabled && before.eon==0);
        assert(before.wet_left==0 && before.wet_right==0);
        assert(before.frames==audio.sample_index && before.frames>=prior_reverb.frames);
        for(i=0;i<32;++i) assert(before.coefficients[i]==trace[i+2].value);
        /* Separate real device advancement after the source return proves
         * that bit80 drives RAM processing even with zero output depth.
         * No host sleep, observer read-driven clock, or manual completion. */
        assert(musashi_spu_cd_audio_advance(f.audio,source_end+768u*100u));
        assert(musashi_spu_cd_audio_reverb_snapshot(f.audio,&after));
        assert(after.frames==before.frames+100);
        assert(after.processed_left>before.processed_left && after.processed_right>before.processed_right);
        assert(after.ram_writes>before.ram_writes && after.ram_reads>before.ram_reads);
        assert(after.base==0xf204 && after.enabled && after.cursor>=0x79020 && after.cursor<0x80000);
        assert(!(after.cursor&1u));
        assert(after.next_channel==before.next_channel);
        assert(after.unknown_reads==before.unknown_reads && after.unsupported_steps==before.unsupported_steps);
        assert(snapshot().bootstrap_halfwords==32768 && snapshot().manual_halfwords==16);
        assert(snapshot().cycle==source_end+768u*100u && !snapshot().faulted);
        assert(f.cycles==source_end); /* separate source-cost ledger unchanged */
        no_dma_or_bios();
        printf("REVERB_DSP frames=%llu writes=%llu bootstrap=%llu fixture_only=1\n",
            (unsigned long long)after.frames,(unsigned long long)after.ram_writes,
            (unsigned long long)snapshot().bootstrap_halfwords);
    }
    done();
}
static void guard_refusals(void) {
    static const uint32_t guarded[]={0x8003b45c,0x8003b954,0x8003b280};
    static const unsigned retained[]={0,2,35};
    unsigned i;
    for(i=0;i<3;++i) {
        FormatterCpu before; uint64_t cycles;
        prepare(); assert(reverb_run(guarded[i]));
        assert(word(0x8006b0f0)==1 && word(0x800a4ecc)==1);
        put(0x8006b54c,0x1f801c02);
        before=f.cpu; cycles=f.cycles;
        assert(!formatter_step(&f.memory,&f.cpu));
        assert(!memcmp(&before,&f.cpu,sizeof(before)) && f.cycles==cycles);
        assert(trace_count==retained[i]);
        if(i) assert(word(0x8006b0fc)==4 && word(0x8006b0f4)==0xf204);
        if(i==2) coefficient_writes();
        assert(snapshot().control==0xc001 && !snapshot().faulted);
        no_dma_or_bios(); done();
    }
    prepare(); assert(reverb_run(0x8002d1f0));
    /* Test-only argument mutation chooses the real optional-clear branch.
     * No guessed completion: it must stop at the unbound source DMA helper. */
    f.cpu.r[4]=0x104;
    assert(!reverb_run(0x8002c98c) && f.cpu.pc==0x8003c0a0);
    assert(word(0x800a4ed0)==0x104 && word(0x8006b0fc)==4);
    assert(word(0x8006b0f4)==0xf204 && trace_count==34);
    assert(f.cpu.r[31]==0x8003b8e0);
    coefficient_writes(); no_dma_or_bios();
    assert(snapshot().control==0xc001 && !snapshot().faulted);
    { MusashiSpuReverbSnapshot r;
      assert(musashi_spu_cd_audio_reverb_snapshot(f.audio,&r));
      assert(r.base==0xfffe && !r.enabled); }
    done();
}
int main(int argc,char **argv) {
    FILE *file;
    assert(argc==2); file=fopen(argv[1],"rb"); assert(file);
    assert(fread(exe,1,sizeof(exe),file)==sizeof(exe) && fgetc(file)==EOF);
    assert(!fclose(file));
    success(); guard_refusals();
    puts("SPU_REVERB_SOURCE_PASS fixture_only=1"); return 0;
}

#include "musashi_spu_cd_audio.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const uint16_t mode4[32]={
 0x00e3,0x00a9,0x6f60,0x4fa8,0xbce0,0x4510,0xbef0,0xa680,
 0x5680,0x52c0,0x0dfb,0x0b58,0x0d09,0x0a3c,0x0bd9,0x0973,
 0x0b59,0x08da,0x08d9,0x05e9,0x07ec,0x04b0,0x06ef,0x03d2,
 0x05ea,0x031d,0x031c,0x0238,0x0154,0x00aa,0x8000,0x8000
};
typedef struct Sink { int16_t pcm[32768*2]; size_t frames,calls,refuse; } Sink;
static int ready(void *p) { (void)p;return 1; }
static uint64_t token(void *p) { (void)p;return 1; }
static int status(void *p,size_t *n,int *playing) { (void)p;*n=0;*playing=1;return 1; }
static int queue(void *p,const int16_t *pcm,size_t n) {
    Sink *s=p;++s->calls;
    if(s->refuse && s->calls==s->refuse) return 0;
    assert(n<=32768-s->frames);memcpy(s->pcm+s->frames*2,pcm,n*4);s->frames+=n;return 1;
}
static MusashiSpuCdAudio *create(Sink *s) {
    MusashiSpuCdAudioBackend b={s,ready,token,status,queue};
    MusashiSpuCdAudio *a=musashi_spu_cd_audio_create();
    assert(a && musashi_spu_cd_audio_init_bios_muted(a,&b,0));return a;
}
static void wr(MusashiSpuCdAudio *a,unsigned offset,uint16_t v) {
    assert(musashi_spu_cd_audio_write16(a,0x1f801c00u+offset,v));
}
static void advance(MusashiSpuCdAudio *a,uint64_t sample) {
    assert(musashi_spu_cd_audio_advance(a,sample*768));
}
static MusashiSpuReverbSnapshot snap(MusashiSpuCdAudio *a) {
    MusashiSpuReverbSnapshot s;assert(musashi_spu_cd_audio_reverb_snapshot(a,&s));return s;
}
static void preset(MusashiSpuCdAudio *a) {
    unsigned i;for(i=0;i<32;++i) wr(a,0x1c0+i*2,mode4[i]);wr(a,0x1a2,0xf204);
}
static void gains(MusashiSpuCdAudio *a,int wet) {
    wr(a,0x180,0x3fff);wr(a,0x182,0x3fff);
    wr(a,0x1b0,0x7fff);wr(a,0x1b2,0x7fff);
    wr(a,0x184,(uint16_t)wet);wr(a,0x186,(uint16_t)wet);
}
static void put(MusashiSpuCdAudio *a,uint32_t address,int16_t value) {
    assert(!(address&7));wr(a,0x1ac,4);wr(a,0x1a6,(uint16_t)(address/8));wr(a,0x1a8,(uint16_t)value);
}
static int16_t get(MusashiSpuCdAudio *a,uint32_t address) {
    uint8_t b[2];unsigned v;assert(musashi_spu_cd_audio_copy_ram(a,address,b,2));
    v=b[0]|((unsigned)b[1]<<8);return (int16_t)(v>=32768?(int)v-65536:(int)v);
}
static void test_bootstrap_and_history(void) {
    Sink *s=calloc(1,sizeof(*s));MusashiSpuCdAudio *a=create(s);
    uint8_t bytes[65536],guard;size_t i;MusashiSpuCdAudioSnapshot m;
    MusashiSpuReverbSnapshot r;
    assert(musashi_spu_cd_audio_copy_ram(a,0x70000,bytes,sizeof(bytes)));
    for(i=0;i<sizeof(bytes);++i) assert(bytes[i]==0);
    assert(!musashi_spu_cd_audio_copy_ram(a,0x6ffff,&guard,1));
    assert(!musashi_spu_cd_audio_copy_ram(a,0,&guard,1));
    assert(musashi_spu_cd_audio_snapshot(a,&m));
    assert(m.bootstrap_halfwords==32768 && m.manual_halfwords==0);
    r=snap(a);assert(r.base==0 && r.frames==0 && r.ram_writes==0);
    advance(a,8192);r=snap(a);
    assert(r.unknown_reads && r.unknown_history_left && r.unknown_history_right);
    assert(r.first_unknown_address==0x1000 && r.ram_writes==0);
    for(i=0;i<s->frames*2;++i) assert(s->pcm[i]==0);
    /* Real source order: old FFFE, partial coefficients, F204, enable. */
    wr(a,0x1a2,0xfffe);
    for(i=0;i<32;++i) { wr(a,0x1c0+(unsigned)i*2,mode4[i]);advance(a,8193+i); }
    r=snap(a);assert(r.unsupported_steps && r.frames==8224);
    wr(a,0x1a2,0xf204);wr(a,0x1aa,0xc080);advance(a,8225);
    r=snap(a);assert(r.ram_writes==4 && r.unknown_history_left+r.unknown_history_right>0);
    advance(a,8265);r=snap(a);
    assert(!r.unknown_history_left && !r.unknown_history_right && r.ram_writes==164);
    assert(musashi_spu_cd_audio_destroy(a));free(s);
}
static void test_access_and_reflection(void) {
    Sink *s=calloc(1,sizeof(*s));MusashiSpuCdAudio *a=create(s);MusashiSpuReverbSnapshot r;
    unsigned i,writes=0;const uint32_t addresses[4]={0x7fff8,0x7d6e8,0x7a900,0x79ac0};
    preset(a);
    /* dLSAME uses the real seeded work RAM and negative vWALL. */
    put(a,0x79020+0x0b59*8,16000);wr(a,0x1aa,0xc080);advance(a,2);r=snap(a);
    assert(r.processed_left==1 && r.processed_right==0 && r.cursor==0x79020);
    assert(r.access_count==14 && r.ram_reads==10 && r.ram_writes==4);
    assert(r.accesses[0].address==0x79020+0x0b59*8 && r.accesses[0].value==16000);
    assert(r.accesses[1].address==0x79020+0x0dfb*8-2);
    assert(r.accesses[3].address==0x79020+0x031d*8); /* cross-side dRDIFF */
    for(i=0;i<r.access_count;++i) {
        assert(r.accesses[i].known && !(r.accesses[i].address&1));
        assert(r.accesses[i].address>=0x79020 && r.accesses[i].address<0x80000);
        if(r.accesses[i].write) { assert(writes<4 && r.accesses[i].address==addresses[writes]);++writes; }
    }
    assert(writes==4 && get(a,addresses[0])==-9735);
    /* SAME-2 wraps to actual last halfword at cursor==base for zero offset. */
    wr(a,0x1aa,0xc000);wr(a,0x1d4,0);wr(a,0x1aa,0xc080);advance(a,3);
    wr(a,0x1a2,0xf204);advance(a,4);
    r=snap(a);assert(r.accesses[1].address==0x7fffe);
    assert(!musashi_spu_cd_audio_write16(a,0x1f801dc4,0x8000));
    assert(!musashi_spu_cd_audio_write16(a,0x1f801da2,0xfffe));
    assert(musashi_spu_cd_audio_destroy(a));free(s);
}
static void feed(MusashiSpuCdAudio *a,size_t n) {
    int16_t *p=calloc(n*2,sizeof(*p));size_t i;
    for(i=0;i<512 && i<n;++i) { p[i*2]=12000;p[i*2+1]=-6000; }
    assert(musashi_spu_cd_audio_submit_cd_pcm(a,0,p,n));free(p);
}
static void test_wet_tail_and_chunking(void) {
    Sink *x=calloc(1,sizeof(*x)),*y=calloc(1,sizeof(*y)),*z=calloc(1,sizeof(*z));
    MusashiSpuCdAudio *a=create(x),*b=create(y),*c=create(z);
    size_t i;int nonzero=0,different=0;uint8_t ra[0x6fe0],rb[0x6fe0];
    preset(a);preset(b);preset(c);gains(a,0x6000);gains(b,0x6000);gains(c,0);
    wr(a,0x1aa,0xc085);wr(b,0x1aa,0xc085);wr(c,0x1aa,0xc085);
    feed(a,8192);feed(b,8192);feed(c,8192);
    advance(a,8192);for(i=1;i<=8192;++i) advance(b,i);advance(c,8192);
    assert(x->frames==y->frames && !memcmp(x->pcm,y->pcm,x->frames*4));
    assert(musashi_spu_cd_audio_copy_ram(a,0x79020,ra,sizeof(ra)));
    assert(musashi_spu_cd_audio_copy_ram(b,0x79020,rb,sizeof(rb)) && !memcmp(ra,rb,sizeof(ra)));
    for(i=1024;i<8192*2;++i) { if(x->pcm[i]) nonzero=1;if(x->pcm[i]!=z->pcm[i]) different=1; }
    assert(nonzero && different);
    /* Gains alter output only, not feedback storage. */
    assert(musashi_spu_cd_audio_copy_ram(c,0x79020,rb,sizeof(rb)) && !memcmp(ra,rb,sizeof(ra)));
    assert(musashi_spu_cd_audio_destroy(a));assert(musashi_spu_cd_audio_destroy(b));
    assert(musashi_spu_cd_audio_destroy(c));free(x);free(y);free(z);
}
static void test_unknown_and_queue_rollback(void) {
    Sink *x=calloc(1,sizeof(*x)),*y=calloc(1,sizeof(*y));
    MusashiSpuCdAudio *a=create(x),*b=create(y);MusashiSpuCdAudioSnapshot state;
    MusashiSpuReverbSnapshot before,after;uint8_t ra[65536],rb[65536],ca[4096],cb[4096];
    preset(a);preset(b);gains(a,0x7000);gains(b,0x7000);wr(a,0x1aa,0xc085);wr(b,0x1aa,0xc085);
    feed(a,2048);feed(b,2048);x->refuse=2;
    assert(!musashi_spu_cd_audio_advance(a,2048*768));advance(b,1024);
    assert(musashi_spu_cd_audio_snapshot(a,&state) && state.faulted && state.sample_index==1024);
    before=snap(a);after=snap(b);assert(!memcmp(&before,&after,sizeof(before)));
    assert(musashi_spu_cd_audio_copy_ram(a,0x70000,ra,sizeof(ra)));
    assert(musashi_spu_cd_audio_copy_ram(b,0x70000,rb,sizeof(rb)) && !memcmp(ra,rb,sizeof(ra)));
    assert(musashi_spu_cd_audio_copy_ram(a,0,ca,sizeof(ca)));
    assert(musashi_spu_cd_audio_copy_ram(b,0,cb,sizeof(cb)) && !memcmp(ca,cb,sizeof(ca)));
    assert(x->frames==1024 && !memcmp(x->pcm,y->pcm,4096));
    assert(musashi_spu_cd_audio_destroy(a));assert(musashi_spu_cd_audio_destroy(b));free(x);free(y);
    x=calloc(1,sizeof(*x));a=create(x);advance(a,8192);before=snap(a);
    wr(a,0x184,1);assert(!musashi_spu_cd_audio_advance(a,8193*768));after=snap(a);
    assert(!memcmp(before.coefficients,after.coefficients,sizeof(before.coefficients)));
    assert(before.frames==after.frames && before.cursor==after.cursor);
    assert(musashi_spu_cd_audio_destroy(a));free(x);
}
static int64_t floorq(int64_t value) {
    return value>=0?value/32768:-((-value+32767)/32768);
}
static void test_fir_and_signed_wet(void) {
    /* Independent measured FIR coefficients; impulse lives in actual RAM.
     * Disabled reverb still reads/output-filters it without feedback writes. */
    static const int16_t h[39]={-1,0,2,0,-10,0,35,0,-103,0,266,0,-616,0,1332,0,
        -2960,0,10246,16384,10246,0,-2960,0,1332,0,-616,0,266,0,-103,0,35,0,-10,0,2,0,-1};
    Sink *x=calloc(1,sizeof(*x));MusashiSpuCdAudio *a=create(x);size_t i;
    wr(a,0x1a2,0xf204);put(a,0x79020,16384);gains(a,0x7fff);
    wr(a,0x186,0x8000);advance(a,43);
    for(i=0;i<43;++i) {
        int64_t l=(i>=1 && i<40)?h[i-1]:0;
        int64_t r=(i>=2 && i<41)?h[i-2]:0;
        l=floorq(floorq(l*32767)*32766);
        r=floorq((-r)*32766);
        assert(x->pcm[i*2]==l && x->pcm[i*2+1]==r);
    }
    assert(snap(a).ram_writes==0 && get(a,0x79020)==16384);
    assert(musashi_spu_cd_audio_destroy(a));free(x);
}
static void test_required_unknown_and_validity_rollback(void) {
    Sink *x=calloc(1,sizeof(*x));MusashiSpuCdAudio *a=create(x);
    uint8_t guard;MusashiSpuCdAudioSnapshot m;
    preset(a);wr(a,0x1a2,0xd000);wr(a,0x1aa,0xc080);
    assert(!musashi_spu_cd_audio_advance(a,2*768));
    assert(musashi_spu_cd_audio_snapshot(a,&m) && m.sample_index==0 && m.faulted);
    assert(!musashi_spu_cd_audio_copy_ram(a,0,&guard,1));
    assert(snap(a).ram_writes==0 && x->frames==0);
    assert(musashi_spu_cd_audio_destroy(a));free(x);
    x=calloc(1,sizeof(*x));a=create(x);preset(a);wr(a,0x1aa,0xc080);x->refuse=1;
    assert(!musashi_spu_cd_audio_advance(a,100*768));
    assert(!musashi_spu_cd_audio_copy_ram(a,0,&guard,1));
    assert(get(a,0x7fff8)==0 && snap(a).frames==0 && snap(a).ram_writes==0);
    assert(musashi_spu_cd_audio_destroy(a));free(x);
}
static void test_voice_send_and_route_gate(void) {
    Sink *x=calloc(1,sizeof(*x)),*y=calloc(1,sizeof(*y));
    MusashiSpuCdAudio *a=create(x),*b=create(y);unsigned j,i;
    uint8_t ra[0x6fe0],rb[0x6fe0];int different=0;
    for(j=0;j<2;++j) {
        MusashiSpuCdAudio *p=j?b:a;
        preset(p);gains(p,0x6000);wr(p,0x1ac,4);wr(p,0x1a6,0x200);wr(p,0x1a8,0x0700);
        for(i=0;i<7;++i) wr(p,0x1a8,0x7777);
        wr(p,0,0x3fff);wr(p,2,0x2000);wr(p,4,0x1000);wr(p,6,0x200);
        wr(p,8,0xf);wr(p,10,0x1fc0);wr(p,0x198,j?0:1);wr(p,0x1aa,0xc080);wr(p,0x188,1);
        advance(p,8192);
    }
    assert(musashi_spu_cd_audio_copy_ram(a,0x79020,ra,sizeof(ra)));
    assert(musashi_spu_cd_audio_copy_ram(b,0x79020,rb,sizeof(rb)) && memcmp(ra,rb,sizeof(ra)));
    for(i=0;i<8192*2;++i) if(x->pcm[i]!=y->pcm[i]) different=1;
    assert(different && snap(a).eon==1 && snap(b).eon==0);
    assert(musashi_spu_cd_audio_destroy(a));assert(musashi_spu_cd_audio_destroy(b));free(x);free(y);
}
static void test_live_adsr_mmio(void) {
    Sink *x=calloc(1,sizeof(*x));MusashiSpuCdAudio *a=create(x);
    MusashiSpuVoiceSnapshot v;unsigned i;
    wr(a,0x1ac,4);wr(a,0x1a6,0x200);wr(a,0x1a8,0x0707);
    for(i=0;i<7;++i) wr(a,0x1a8,0x7777);
    wr(a,4,0x1000);wr(a,6,0x200);wr(a,0x188,1);
    wr(a,8,0x3000); /* pending KON: shift12 adds half counter per sample */
    advance(a,2);assert(musashi_spu_cd_audio_voice_snapshot(a,0,&v) && v.envelope==0);
    wr(a,8,0x3100);wr(a,10,0x1fc0); /* live attack step becomes6; retain half counter */
    advance(a,3);assert(musashi_spu_cd_audio_voice_snapshot(a,0,&v));
    assert(v.envelope==6 && v.registers[4]==0x3100 && v.registers[5]==0x1fc0);
    assert(musashi_spu_cd_audio_destroy(a));free(x);
}
int main(void) {
    test_bootstrap_and_history();test_access_and_reflection();
    test_wet_tail_and_chunking();test_unknown_and_queue_rollback();
    test_fir_and_signed_wet();test_required_unknown_and_validity_rollback();
    test_voice_send_and_route_gate();test_live_adsr_mmio();
    puts("SPU_REVERB_PASS");return 0;
}

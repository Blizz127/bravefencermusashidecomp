#include "musashi_audio_sdl.h"

#include <SDL.h>

#include <limits.h>
#include <stdlib.h>
#include <string.h>

struct MusashiAudioSdl {
    SDL_AudioDeviceID device;
    uint64_t owner_thread;
    SDL_AudioSpec obtained;
    MusashiSpuCdAudioBackend backend;
    int subsystem_ref;
    int opened;
    int faulted;
};

static int sdl_thread_ok(MusashiAudioSdl *audio) {
    uint64_t current = (uint64_t)SDL_ThreadID();
    if (!audio || audio->owner_thread == 0 || current == 0 ||
        current != audio->owner_thread) {
        if (audio) audio->faulted = 1;
        return 0;
    }
    return 1;
}

static int sdl_is_dummy_driver(void) {
    const char *driver = SDL_GetCurrentAudioDriver();
    return driver && (!strcmp(driver, "dummy") || !strcmp(driver, "disk"));
}

static int sdl_ready(void *userdata) {
    MusashiAudioSdl *audio = userdata;
    return audio && audio->opened && !audio->faulted && sdl_thread_ok(audio) &&
           audio->device != 0 &&
           SDL_GetAudioDeviceStatus(audio->device) == SDL_AUDIO_PLAYING;
}

static uint64_t sdl_thread_token(void *userdata) {
    (void)userdata;
    return (uint64_t)SDL_ThreadID();
}

static int sdl_status_backend(void *userdata, size_t *queued_frames,
                              int *playing) {
    MusashiAudioSdl *audio = userdata;
    Uint32 queued_bytes;
    SDL_AudioStatus state;
    if (!audio || !audio->opened || audio->faulted || !queued_frames || !playing ||
        !sdl_thread_ok(audio)) return 0;
    state = SDL_GetAudioDeviceStatus(audio->device);
    queued_bytes = SDL_GetQueuedAudioSize(audio->device);
    if ((queued_bytes % (sizeof(int16_t) * 2u)) != 0u) return 0;
    if (state != SDL_AUDIO_PLAYING) {
        audio->faulted = 1;
        return 0;
    }
    *queued_frames = queued_bytes / (sizeof(int16_t) * 2u);
    *playing = 1;
    return 1;
}

static int sdl_queue_backend(void *userdata, const int16_t *stereo_pcm,
                             size_t frames) {
    MusashiAudioSdl *audio = userdata;
    size_t bytes;
    Uint32 queued_bytes;
    if (!audio || !audio->opened || audio->faulted || !stereo_pcm ||
        !sdl_thread_ok(audio) ||
        frames > MUSASHI_SPU_CD_AUDIO_QUEUE_LIMIT ||
        frames > SIZE_MAX / (sizeof(int16_t) * 2u))
        return 0;
    bytes = frames * sizeof(int16_t) * 2u;
    queued_bytes = SDL_GetQueuedAudioSize(audio->device);
    if ((queued_bytes % (sizeof(int16_t) * 2u)) != 0u ||
        SDL_GetAudioDeviceStatus(audio->device) != SDL_AUDIO_PLAYING ||
        queued_bytes / (sizeof(int16_t) * 2u) > MUSASHI_SPU_CD_AUDIO_QUEUE_LIMIT ||
        bytes > UINT32_MAX ||
        frames > MUSASHI_SPU_CD_AUDIO_QUEUE_LIMIT -
                      queued_bytes / (sizeof(int16_t) * 2u) ||
        SDL_QueueAudio(audio->device, stereo_pcm, (Uint32)bytes) != 0) {
        audio->faulted = 1;
        return 0;
    }
    return 1;
}

MusashiAudioSdl *musashi_audio_sdl_create(void) {
    return calloc(1, sizeof(MusashiAudioSdl));
}

int musashi_audio_sdl_open(MusashiAudioSdl *audio) {
    SDL_AudioSpec want;
    if (!audio || audio->opened || audio->subsystem_ref) return 0;
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) return 0;
    audio->subsystem_ref = 1;
    if (sdl_is_dummy_driver()) goto fail;
    memset(&want, 0, sizeof(want));
    want.freq = 44100;
    want.format = AUDIO_S16SYS;
    want.channels = 2;
    want.samples = 1024;
    want.callback = NULL;
    audio->device = SDL_OpenAudioDevice(NULL, 0, &want, &audio->obtained, 0);
    audio->owner_thread = (uint64_t)SDL_ThreadID();
    if (!audio->device || audio->obtained.freq != 44100 ||
        audio->obtained.format != AUDIO_S16SYS || audio->obtained.channels != 2 ||
        audio->owner_thread == 0)
        goto fail;
    SDL_PauseAudioDevice(audio->device, 0);
    if (SDL_GetAudioDeviceStatus(audio->device) != SDL_AUDIO_PLAYING)
        goto fail;
    audio->backend.userdata = audio;
    audio->backend.ready = sdl_ready;
    audio->backend.thread_token = sdl_thread_token;
    audio->backend.status = sdl_status_backend;
    audio->backend.queue = sdl_queue_backend;
    audio->opened = 1;
    return 1;

fail:
    if (audio->device) {
        SDL_CloseAudioDevice(audio->device);
        audio->device = 0;
    }
    if (audio->subsystem_ref) {
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        audio->subsystem_ref = 0;
    }
    return 0;
}

const MusashiSpuCdAudioBackend *musashi_audio_sdl_backend(
    const MusashiAudioSdl *audio) {
    if (!audio || !audio->opened || audio->faulted ||
        !sdl_thread_ok((MusashiAudioSdl *)audio)) return NULL;
    return &audio->backend;
}

int musashi_audio_sdl_status(const MusashiAudioSdl *audio,
                             MusashiAudioSdlStatus *status) {
    Uint32 queued_bytes;
    SDL_AudioStatus state;
    if (!audio || !audio->opened || !status ||
        !sdl_thread_ok((MusashiAudioSdl *)audio)) return 0;
    queued_bytes = SDL_GetQueuedAudioSize(audio->device);
    if (queued_bytes % (sizeof(int16_t) * 2u) != 0u) return 0;
    state = SDL_GetAudioDeviceStatus(audio->device);
    status->frequency = (uint32_t)audio->obtained.freq;
    status->format = (uint16_t)audio->obtained.format;
    status->channels = audio->obtained.channels;
    status->queued_frames = queued_bytes / (sizeof(int16_t) * 2u);
    status->playing = state == SDL_AUDIO_PLAYING;
    status->faulted = audio->faulted;
    return 1;
}

int musashi_audio_sdl_close(MusashiAudioSdl *audio) {
    if (!audio) return 0;
    if (audio->opened && !sdl_thread_ok(audio)) return 0;
    if (audio->device) {
        SDL_ClearQueuedAudio(audio->device);
        SDL_CloseAudioDevice(audio->device);
        audio->device = 0;
    }
    audio->opened = 0;
    if (audio->subsystem_ref) {
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        audio->subsystem_ref = 0;
    }
    audio->owner_thread = 0;
    return 1;
}

int musashi_audio_sdl_destroy(MusashiAudioSdl *audio) {
    if (!audio) return 0;
    if (!musashi_audio_sdl_close(audio)) return 0;
    free(audio);
    return 1;
}

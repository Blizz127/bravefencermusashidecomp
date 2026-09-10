#include "musashi_disc_media.h"

#include <openssl/evp.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    PINNED_CUE_SIZE = 250,
    PINNED_BIN_SIZE = 416021760,
    PINNED_TOTAL_FRAMES = 176880,
    PINNED_TRACK_COUNT = 4,
    READ_CHUNK = 1024 * 1024
};

struct MusashiDiscMedia {
    unsigned char *image;
    MusashiDiscMediaInfo info;
};

static int hex_value(char value) {
    if (value >= '0' && value <= '9') return value - '0';
    if (value >= 'a' && value <= 'f') return value - 'a' + 10;
    if (value >= 'A' && value <= 'F') return value - 'A' + 10;
    return -1;
}

static int sha256_matches(const unsigned char *data, size_t size,
                          const char *expected_hex) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_size = 0;
    size_t i;

    if (!data || !expected_hex || strlen(expected_hex) != 64u ||
        EVP_Digest(data, size, digest, &digest_size, EVP_sha256(), NULL) != 1 ||
        digest_size != 32u)
        return 0;
    for (i = 0; i < 32u; ++i) {
        int high = hex_value(expected_hex[i * 2u]);
        int low = hex_value(expected_hex[i * 2u + 1u]);
        if (high < 0 || low < 0 || digest[i] != (unsigned char)((high << 4) | low))
            return 0;
    }
    return 1;
}

static int read_file_bytes(const char *path, unsigned char *destination,
                           size_t expected_size) {
    FILE *file;
    long length;
    size_t offset = 0;
    int close_ok;

    if (!path || !destination) return 0;
    file = fopen(path, "rb");
    if (!file) return 0;
    if (fseek(file, 0, SEEK_END) != 0 || (length = ftell(file)) < 0 ||
        (unsigned long)length != (unsigned long)expected_size ||
        fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return 0;
    }
    while (offset < expected_size) {
        size_t request = expected_size - offset;
        size_t count = request > READ_CHUNK ? READ_CHUNK : request;
        size_t got = fread(destination + offset, 1, count, file);
        offset += got;
        if (got != count) break;
    }
    close_ok = fclose(file) == 0;
    return close_ok && offset == expected_size;
}

static int file_has_exact_size(const char *path, size_t expected_size) {
    FILE *file;
    long length;
    int close_ok;

    if (!path) return 0;
    file = fopen(path, "rb");
    if (!file) return 0;
    if (fseek(file, 0, SEEK_END) != 0 || (length = ftell(file)) < 0)
        close_ok = 0;
    else
        close_ok = (unsigned long)length == (unsigned long)expected_size;
    if (fclose(file) != 0) close_ok = 0;
    return close_ok;
}

static int validate_cue(const char *cue_path) {
    unsigned char cue[PINNED_CUE_SIZE];
    return read_file_bytes(cue_path, cue, sizeof(cue)) &&
           sha256_matches(cue, sizeof(cue),
                          "85326d3f735d603a9d37f0e0754a37a52cc9d0bf6b8b4ce566c4fa54f6fdee5c");
}

static void fill_info(MusashiDiscMediaInfo *info) {
    memset(info, 0, sizeof(*info));
    info->sector_size = MUSASHI_DISC_RAW_SECTOR_SIZE;
    info->total_frames = PINNED_TOTAL_FRAMES;
    info->track_count = PINNED_TRACK_COUNT;

    info->tracks[0].number = 1;
    info->tracks[0].index00_frame = 0;
    info->tracks[0].index01_frame = 0;
    info->tracks[0].first_frame = 0;
    info->tracks[0].end_frame = 155122;
    info->tracks[0].mode = MUSASHI_DISC_TRACK_MODE2_2352;

    info->tracks[1].number = 2;
    info->tracks[1].index00_frame = 155122;
    info->tracks[1].index01_frame = 155272;
    info->tracks[1].first_frame = 155272;
    info->tracks[1].end_frame = 159662;
    info->tracks[1].mode = MUSASHI_DISC_TRACK_AUDIO;

    info->tracks[2].number = 3;
    info->tracks[2].index00_frame = 159662;
    info->tracks[2].index01_frame = 159812;
    info->tracks[2].first_frame = 159812;
    info->tracks[2].end_frame = 162778;
    info->tracks[2].mode = MUSASHI_DISC_TRACK_AUDIO;

    info->tracks[3].number = 4;
    info->tracks[3].index00_frame = 162778;
    info->tracks[3].index01_frame = 162928;
    info->tracks[3].first_frame = 162928;
    info->tracks[3].end_frame = PINNED_TOTAL_FRAMES;
    info->tracks[3].mode = MUSASHI_DISC_TRACK_AUDIO;
}

MusashiDiscMedia *musashi_disc_media_open_pinned(const char *cue_path,
                                                 const char *bin_path) {
    unsigned char *image;
    MusashiDiscMedia *media;

    if (!validate_cue(cue_path)) return NULL;
    if (!file_has_exact_size(bin_path, PINNED_BIN_SIZE)) return NULL;
    image = malloc(PINNED_BIN_SIZE);
    if (!image) return NULL;
    if (!read_file_bytes(bin_path, image, PINNED_BIN_SIZE) ||
        !sha256_matches(image, PINNED_BIN_SIZE,
                        "0a53702937d74e20d99fee9a29a80f7e91da762e66958819d531173939a50879")) {
        free(image);
        return NULL;
    }
    media = calloc(1, sizeof(*media));
    if (!media) {
        free(image);
        return NULL;
    }
    media->image = image;
    fill_info(&media->info);
    return media;
}

int musashi_disc_media_get_info(const MusashiDiscMedia *media,
                                MusashiDiscMediaInfo *info) {
    if (!media || !media->image || !info) return 0;
    *info = media->info;
    return 1;
}

int musashi_disc_media_read_sector(const MusashiDiscMedia *media,
                                   uint32_t file_frame, void *output,
                                   size_t output_size) {
    size_t offset;

    if (!media || !media->image || !output ||
        output_size < MUSASHI_DISC_RAW_SECTOR_SIZE ||
        file_frame >= media->info.total_frames)
        return 0;
    offset = (size_t)file_frame * MUSASHI_DISC_RAW_SECTOR_SIZE;
    memcpy(output, media->image + offset, MUSASHI_DISC_RAW_SECTOR_SIZE);
    return 1;
}

void musashi_disc_media_close(MusashiDiscMedia *media) {
    if (!media) return;
    free(media->image);
    media->image = NULL;
    free(media);
}

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <time.h>

#define W 256
#define H 256
#define TW 32
#define TH 32
#define PIXELS (W * H)
#define TP (TW * TH)

typedef struct {
    int x;
    int y;
    int64_t score;
} Result;

static double wall_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

static Result match_ssd(const uint8_t *image, const uint8_t *T) {
    Result best = {-1, -1, INT64_MAX};

    for (int y = 0; y <= H - TH; y++) {
        for (int x = 0; x <= W - TW; x++) {
            int64_t score = 0;

            for (int i = 0; i < TH; i++) {
                for (int j = 0; j < TW; j++) {
                    int a = image[(y + i) * W + (x + j)];
                    int b = T[i * TW + j];
                    int diff = a - b;
                    score += (int64_t)diff * diff;
                }
            }

            if (score < best.score) {
                best.score = score;
                best.x = x;
                best.y = y;
            }
        }
    }

    return best;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s DATA_DIR N OUTPUT.csv\n", argv[0]);
        return 1;
    }

    const char *dir = argv[1];
    int N = atoi(argv[2]);
    const char *outpath = argv[3];

    if (N <= 0) {
        fprintf(stderr, "N must be positive.\n");
        return 1;
    }

    uint8_t T[TP];

    FILE *tf = fopen("/kaggle/working/ssd_project/data/template.bin", "rb");
    if (!tf || fread(T, 1, TP, tf) != TP) {
        fprintf(stderr, "Cannot read template.bin\n");
        if (tf) fclose(tf);
        return 1;
    }
    fclose(tf);

    FILE *out = fopen(outpath, "w");
    if (!out) {
        perror("Cannot create output CSV");
        return 1;
    }

    fprintf(out, "image_id,x,y,ssd\n");

    double start = wall_time();

    for (int k = 0; k < N; k++) {
        char path[512];
        snprintf(path, sizeof(path), "%s/%06d.bin", dir, k);

        FILE *f = fopen(path, "rb");
        if (!f) {
            fprintf(stderr, "Cannot open %s\n", path);
            fclose(out);
            return 1;
        }

        uint8_t *img = malloc(PIXELS);
        if (!img || fread(img, 1, PIXELS, f) != PIXELS) {
            fprintf(stderr, "Cannot read image %s\n", path);
            free(img);
            fclose(f);
            fclose(out);
            return 1;
        }

        fclose(f);

        Result r = match_ssd(img, T);

        fprintf(out, "%d,%d,%d,%" PRId64 "\n",
                k, r.x, r.y, r.score);

        free(img);
    }

    double elapsed = wall_time() - start;
    fclose(out);

    printf("Sequential wall time: %.6f seconds\n", elapsed);
    printf("Results saved to: %s\n", outpath);

    return 0;
}

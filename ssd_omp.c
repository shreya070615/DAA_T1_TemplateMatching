
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

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

static int load_template(const char *dir, uint8_t *T) {
    char path[1024];
    FILE *f = NULL;

    if (dir) {
        snprintf(path, sizeof(path), "%s/template.bin", dir);
        f = fopen(path, "rb");
    }

    if (!f) {
        snprintf(path, sizeof(path), "./template.bin");
        f = fopen(path, "rb");
    }

    if (!f) {
        snprintf(path, sizeof(path),
                 "/kaggle/working/ssd_project/data/template.bin");
        f = fopen(path, "rb");
    }

    if (!f) {
        fprintf(stderr,
                "Cannot read template.bin. Expected it in %s/template.bin, ./template.bin, or the Kaggle default path.\n",
                dir ? dir : ".");
        return 0;
    }

    if (fread(T, 1, TP, f) != TP) {
        fprintf(stderr, "Template file %s is incomplete.\n", path);
        fclose(f);
        return 0;
    }

    fclose(f);
    return 1;
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
    if (!load_template(dir, T)) {
        return 1;
    }

    Result *results = calloc((size_t)N, sizeof(Result));
    if (!results) {
        perror("Cannot allocate results");
        return 1;
    }

    int failed = 0;
    double start = wall_time();

    #pragma omp parallel for schedule(static) reduction(|:failed)
    for (int k = 0; k < N; k++) {
        char path[512];
        snprintf(path, sizeof(path), "%s/%06d.bin", dir, k);

        FILE *f = fopen(path, "rb");
        if (!f) {
            #pragma omp critical
            fprintf(stderr, "Cannot open %s\n", path);
            failed = 1;
            continue;
        }

        uint8_t *img = malloc(PIXELS);
        if (!img || fread(img, 1, PIXELS, f) != PIXELS) {
            #pragma omp critical
            fprintf(stderr, "Cannot read image %s\n", path);
            free(img);
            fclose(f);
            failed = 1;
            continue;
        }

        fclose(f);
        results[k] = match_ssd(img, T);
        free(img);
    }

    if (failed) {
        free(results);
        return 1;
    }

    FILE *out = fopen(outpath, "w");
    if (!out) {
        perror("Cannot create output CSV");
        free(results);
        return 1;
    }

    fprintf(out, "image_id,x,y,ssd\n");

    for (int k = 0; k < N; k++) {
        fprintf(out, "%d,%d,%d,%" PRId64 "\n",
                k, results[k].x, results[k].y,
                results[k].score);
    }

    fclose(out);
    free(results);

    printf("OpenMP threads: %d\n", omp_get_max_threads());
    printf("OpenMP wall time: %.6f seconds\n",
           wall_time() - start);
    printf("Results saved to: %s\n", outpath);

    return 0;
}

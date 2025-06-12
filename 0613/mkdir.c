#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <libgen.h>

#define MODE_DEFAULT 0777

// -p 옵션: 상위 디렉터리까지 생성
int mkdir_p(const char *path, mode_t mode) {
    char tmp[1024];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);
    if (tmp[len - 1] == '/')
        tmp[len - 1] = '\0';

    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(tmp, mode) != 0 && errno != EEXIST) {
                perror("mkdir");
                return -1;
            }
            *p = '/';
        }
    }

    if (mkdir(tmp, mode) != 0 && errno != EEXIST) {
        perror("mkdir");
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    mode_t mode = MODE_DEFAULT;
    int opt_p = 0;
    int opt_m = 0;
    char *mode_str = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "pm:")) != -1) {
        switch (opt) {
            case 'p':
                opt_p = 1;
                break;
            case 'm':
                opt_m = 1;
                mode_str = optarg;
                mode = strtol(mode_str, NULL, 8);  // 8진수로 해석
                break;
            default:
                fprintf(stderr, "Usage: %s [-p] [-m mode] dir...\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "mkdir: missing operand\n");
        exit(EXIT_FAILURE);
    }

    for (int i = optind; i < argc; i++) {
        int result;
        if (opt_p) {
            result = mkdir_p(argv[i], mode);
        } else {
            result = mkdir(argv[i], mode);
            if (result != 0) {
                perror("mkdir");
                continue;
            }
        }
    }

    return 0;
}

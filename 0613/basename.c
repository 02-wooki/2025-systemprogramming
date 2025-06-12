#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_help(const char *prog_name) {
    printf("사용법: %s 경로 [접미어]\n", prog_name);
    printf("경로에서 디렉토리 부분을 제거하고 파일 이름만 출력합니다.\n");
    printf("옵션:\n");
    printf("  --help       사용법 출력\n");
    printf("  --version    버전 정보 출력\n");
}

void print_version() {
    printf("basename 구현 버전 1.0\n");
}

const char* get_basename(const char *path) {
    const char *last_slash = strrchr(path, '/');
    return last_slash ? last_slash + 1 : path;
}

void remove_suffix(char *name, const char *suffix) {
    size_t name_len = strlen(name);
    size_t suffix_len = strlen(suffix);
    if (suffix_len <= name_len &&
        strcmp(name + name_len - suffix_len, suffix) == 0) {
        name[name_len - suffix_len] = '\0';
        }
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "사용법: %s 경로 [접미어]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--help") == 0) {
        print_help(argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "--version") == 0) {
        print_version();
        return 0;
    }

    const char *base = get_basename(argv[1]);
    char result[1024];
    strncpy(result, base, sizeof(result));
    result[sizeof(result) - 1] = '\0';

    if (argc == 3) {
        remove_suffix(result, argv[2]);
    }

    printf("%s\n", result);
    return 0;
}

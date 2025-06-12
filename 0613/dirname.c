#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_help(const char *prog_name) {
    printf("사용법: %s 경로\n", prog_name);
    printf("경로에서 마지막 컴포넌트를 제외한 디렉토리 경로를 출력합니다.\n");
    printf("옵션:\n");
    printf("  --help       사용법 출력\n");
    printf("  --version    버전 정보 출력\n");
}

void print_version() {
    printf("dirname 구현 버전 1.0\n");
}

void get_dirname(const char *path, char *output, size_t size) {
    if (path == NULL || strlen(path) == 0) {
        strncpy(output, ".", size);
        return;
    }

    char temp[1024];
    strncpy(temp, path, sizeof(temp));
    temp[sizeof(temp) - 1] = '\0';

    // 경로 끝의 슬래시 제거
    size_t len = strlen(temp);
    while (len > 1 && temp[len - 1] == '/') {
        temp[len - 1] = '\0';
        len--;
    }

    // 마지막 슬래시 찾기
    char *last_slash = strrchr(temp, '/');

    if (last_slash) {
        // 루트인 경우: "/" 하나만 남겨야 함
        if (last_slash == temp) {
            strncpy(output, "/", size);
        } else {
            *last_slash = '\0';
            strncpy(output, temp, size);
        }
    } else {
        strncpy(output, ".", size);
    }

    output[size - 1] = '\0'; // null-terminate
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s 경로\n", argv[0]);
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

    char result[1024];
    get_dirname(argv[1], result, sizeof(result));
    printf("%s\n", result);

    return 0;
}

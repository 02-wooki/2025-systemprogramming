#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEFAULT_LINE_COUNT 10
#define BUFFER_SIZE 4096

void print_help(const char *prog) {
    printf("사용법: %s [옵션]... [파일]\n", prog);
    printf("파일 또는 표준 입력의 처음 몇 줄 또는 바이트를 출력합니다.\n");
    printf("옵션:\n");
    printf("  -n <줄 수>     처음 N줄 출력 (기본값 10줄)\n");
    printf("  -c <바이트 수> 처음 N바이트 출력\n");
    printf("  --help         이 도움말을 출력\n");
    printf("  --version      버전 정보 출력\n");
}

void print_version() {
    printf("head 구현 버전 1.0\n");
}

void print_lines(FILE *fp, int n_lines) {
    char buffer[BUFFER_SIZE];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
        if (++count >= n_lines)
            break;
    }
}

void print_bytes(FILE *fp, int n_bytes) {
    char buffer[BUFFER_SIZE];
    int bytes_read = 0;
    while (bytes_read < n_bytes) {
        int to_read = n_bytes - bytes_read;
        if (to_read > BUFFER_SIZE) to_read = BUFFER_SIZE;

        size_t read_now = fread(buffer, 1, to_read, fp);
        if (read_now == 0) break;

        fwrite(buffer, 1, read_now, stdout);
        bytes_read += read_now;
    }
}

int main(int argc, char *argv[]) {
    int line_mode = 1;             // 기본: 줄 단위
    int count = DEFAULT_LINE_COUNT;
    const char *filename = NULL;

    // 옵션 파싱
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--version") == 0) {
            print_version();
            return 0;
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            count = atoi(argv[++i]);
            line_mode = 1;
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            count = atoi(argv[++i]);
            line_mode = 0;
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "알 수 없는 옵션: %s\n", argv[i]);
            return 1;
        } else {
            filename = argv[i];
        }
    }

    FILE *fp = stdin;
    if (filename) {
        fp = fopen(filename, "r");
        if (!fp) {
            fprintf(stderr, "파일 열기 실패: %s: %s\n", filename, strerror(errno));
            return 1;
        }
    }

    if (line_mode) {
        print_lines(fp, count);
    } else {
        print_bytes(fp, count);
    }

    if (filename) fclose(fp);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEFAULT_LINE_COUNT 10
#define BUFFER_SIZE 4096

void print_help(const char *prog) {
    printf("사용법: %s [옵션]... [파일]\n", prog);
    printf("파일 또는 표준 입력의 마지막 몇 줄 또는 바이트를 출력합니다.\n");
    printf("옵션:\n");
    printf("  -n <줄 수>     마지막 N줄 출력 (기본값 10줄)\n");
    printf("  -c <바이트 수> 마지막 N바이트 출력\n");
    printf("  --help         이 도움말을 출력\n");
    printf("  --version      버전 정보 출력\n");
}

void print_version() {
    printf("tail 구현 버전 1.0\n");
}

void print_last_lines(FILE *fp, int n_lines) {
    char **lines = malloc(sizeof(char*) * n_lines);
    int count = 0;
    char buffer[BUFFER_SIZE];

    for (int i = 0; i < n_lines; i++) lines[i] = NULL;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (lines[count % n_lines]) {
            free(lines[count % n_lines]);
        }
        lines[count % n_lines] = strdup(buffer);
        count++;
    }

    int start = count >= n_lines ? count % n_lines : 0;
    int lines_to_print = count < n_lines ? count : n_lines;

    for (int i = 0; i < lines_to_print; i++) {
        printf("%s", lines[(start + i) % n_lines]);
    }

    for (int i = 0; i < n_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}

void print_last_bytes(FILE *fp, int n_bytes) {
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size < 0) {
        perror("파일 크기 확인 실패");
        return;
    }

    long start = size - n_bytes;
    if (start < 0) start = 0;

    fseek(fp, start, SEEK_SET);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
}

int main(int argc, char *argv[]) {
    int line_mode = 1;
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
        print_last_lines(fp, count);
    } else {
        print_last_bytes(fp, count);
    }

    if (filename) fclose(fp);
    return 0;
}

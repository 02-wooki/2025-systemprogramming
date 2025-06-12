#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 1024

// 옵션 플래그
bool opt_b = false; // 번호 매기되 않은 빈 줄 제외하고 줄 번호 붙임
bool opt_n = false; // 모든 줄에 줄 번호 붙임
bool opt_s = false; // 연속된 빈 줄을 하나로 축소
bool opt_E = false; // 각 줄 끝에 $
bool opt_A = false; // -vET: 출력 불가능한 문자 시각화 + E + T 처리

int printFileWithOptions(FILE *fp) {
    char line[BUFFER_SIZE];
    int line_number = 1;
    bool prev_blank = false;

    while (fgets(line, BUFFER_SIZE, fp)) {
        bool is_blank = (line[0] == '\n');

        if (opt_s && is_blank && prev_blank)
            continue; // 연속된 빈 줄 제거

        prev_blank = is_blank;

        if (opt_b && is_blank == false) {
            printf("%6d\t", line_number++);
        } else if (opt_n && !opt_b) {
            printf("%6d\t", line_number++);
        }

        for (int i = 0; line[i] != '\0' && line[i] != '\n'; ++i) {
            unsigned char c = line[i];

            if (opt_A) {
                if (c == '\t') {
                    printf("^I");
                } else if (c < 32 && c != '\n') {
                    printf("^%c", c + 64);
                } else if (c == 127) {
                    printf("^?");
                } else {
                    putchar(c);
                }
            } else {
                putchar(c);
            }
        }

        if (opt_E || opt_A) {
            if (line[strlen(line) - 1] == '\n')
                printf("$\n");
        } else {
            if (line[strlen(line) - 1] == '\n')
                printf("\n");
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int file_start = 1;

    // 옵션 파싱
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            file_start = i;
            break;
        }
        file_start = i + 1;

        if (argv[i][1] == '-') {
            int start = 2, end = strlen(argv[i]);
            char fullOpt[end - start + 1];
            for (int j = start; j < end; j++)
                fullOpt[j - start] = argv[i][j];
            fullOpt[end - start] = '\0';

            if (!strcmp(fullOpt, "number-nonblank"))
                opt_b = true;
            else if (!strcmp(fullOpt, "number"))
                opt_n = true;
            else if (!strcmp(fullOpt, "squeeze-blank"))
                opt_s = true;
            else if (!strcmp(fullOpt, "show-ends"))
                opt_E = true;
            else if (!strcmp(fullOpt, "show-all"))
                opt_A = true;
            else {
                fprintf(stderr, "cat: invalid option -- '%s'\n", argv[i]);
                exit(1);
            }
            break;
        }

        for (int j = 1; argv[i][j]; j++) {
            switch (argv[i][j]) {
                case 'b': opt_b = true; break;
                case 'n': opt_n = true; break;
                case 's': opt_s = true; break;
                case 'E': opt_E = true; break;
                case 'A': opt_A = true; opt_E = true; break;
                default:
                    fprintf(stderr, "cat: invalid option -- '%c'\n", argv[i][j]);
                    exit(1);
            }
        }
    }

    if (file_start >= argc) {
        printFileWithOptions(stdin);
        printf("\n");
        exit(0);
    }

    for (int i = file_start; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
            continue;
        }

        printFileWithOptions(fp);
        fclose(fp);
    }

    return 0;
}

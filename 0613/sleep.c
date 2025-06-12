#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

// 접미사 단위 변환 (초 단위)
long suffix_to_seconds(char suffix) {
    switch (suffix) {
        case 's': return 1;
        case 'm': return 60;
        case 'h': return 3600;
        case 'd': return 86400;
        default: return -1;
    }
}

int parse_sleep_argument(const char *arg, long *total_seconds) {
    size_t len = strlen(arg);
    if (len == 0) return -1;

    char unit = 's'; // 기본 단위: 초
    char number_part[32];

    if (isalpha(arg[len - 1])) {
        unit = arg[len - 1];
        strncpy(number_part, arg, len - 1);
        number_part[len - 1] = '\0';
    } else {
        strncpy(number_part, arg, len);
        number_part[len] = '\0';
    }

    char *endptr;
    double value = strtod(number_part, &endptr);
    if (*endptr != '\0') return -1;

    long multiplier = suffix_to_seconds(unit);
    if (multiplier == -1) return -1;

    *total_seconds = (long)(value * multiplier);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s 시간\n", argv[0]);
        fprintf(stderr, "예시: %s 5s | 2m | 1h | 1d\n", argv[0]);
        return 1;
    }

    long seconds = 0;
    if (parse_sleep_argument(argv[1], &seconds) != 0 || seconds < 0) {
        fprintf(stderr, "잘못된 시간 형식입니다: %s\n", argv[1]);
        return 1;
    }

    sleep(seconds);

    return 0;
}

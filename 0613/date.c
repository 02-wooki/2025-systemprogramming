#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct tm timeinfo;
    time_t rawtime;
    char buffer[100];

    // 인자가 없는 경우: 현재 시간 출력
    if (argc == 1) {
        time(&rawtime);
        localtime_r(&rawtime, &timeinfo);
        strftime(buffer, sizeof(buffer), "%a %b %d %T %Y", &timeinfo);
        printf("%s\n", buffer);
        return 0;
    }

    // -d 옵션 처리
    if (argc == 3 && strcmp(argv[1], "-d") == 0) {
        memset(&timeinfo, 0, sizeof(struct tm));

        // 날짜 문자열 파싱
        if (strptime(argv[2], "%Y-%m-%d %H:%M:%S", &timeinfo) == NULL &&
            strptime(argv[2], "%Y-%m-%d", &timeinfo) == NULL) {
            fprintf(stderr, "날짜 형식 오류: 지원 형식은 'YYYY-MM-DD' 또는 'YYYY-MM-DD HH:MM:SS'\n");
            exit(1);
        }

        // 로컬 시간대로 처리하여 struct tm → time_t 변환
        rawtime = mktime(&timeinfo);
        if (rawtime == -1) {
            fprintf(stderr, "날짜 변환 실패\n");
            return 1;
        }

        strftime(buffer, sizeof(buffer), "%a %b %d %T %Y", &timeinfo);
        printf("%s\n", buffer);
        exit(0);
    }

    // +포맷 처리
    if (argc == 2 && argv[1][0] == '+') {
        time(&rawtime);
        localtime_r(&rawtime, &timeinfo);
        strftime(buffer, sizeof(buffer), argv[1] + 1, &timeinfo);
        printf("%s\n", buffer);
        exit(0);
    }

    // 잘못된 사용
    fprintf(stderr, "사용법:\n");
    fprintf(stderr, "  %s             → 현재 날짜/시간 출력\n", argv[0]);
    fprintf(stderr, "  %s +FORMAT     → 포맷 출력 (예: +%%Y-%%m-%%d)\n", argv[0]);
    fprintf(stderr, "  %s -d \"날짜\"   → 특정 날짜 출력 (예: \"2024-12-31\" 또는 \"2024-12-31 13:30:00\")\n", argv[0]);
    exit(1);
}

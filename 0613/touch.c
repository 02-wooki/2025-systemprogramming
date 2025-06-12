#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

int parse_time_string(const char *str, struct utimbuf *utb) {
    struct tm tm = {0};
    time_t t;

    if (strlen(str) != 12 && strlen(str) != 14) {
        fprintf(stderr, "시간 형식 오류: [[CC]YY]MMDDhhmm\n");
        return -1;
    }

    // [[CC]YY]MMDDhhmm
    int offset = 0;

    if (strlen(str) == 14) {
        // CCYY
        tm.tm_year = (str[0]-'0')*1000 + (str[1]-'0')*100 + (str[2]-'0')*10 + (str[3]-'0');
        tm.tm_year -= 1900;
        offset = 4;
    } else {
        // Assume 20YY
        tm.tm_year = (str[0]-'0')*10 + (str[1]-'0') + 100; // since 1900
        offset = 2;
    }

    tm.tm_mon  = (str[offset+0]-'0')*10 + (str[offset+1]-'0') - 1;
    tm.tm_mday = (str[offset+2]-'0')*10 + (str[offset+3]-'0');
    tm.tm_hour = (str[offset+4]-'0')*10 + (str[offset+5]-'0');
    tm.tm_min  = (str[offset+6]-'0')*10 + (str[offset+7]-'0');
    tm.tm_sec  = 0;

    t = mktime(&tm);
    if (t == -1) {
        perror("시간 변환 실패");
        return -1;
    }

    utb->actime = utb->modtime = t;
    return 0;
}

int main(int argc, char *argv[]) {
    int opt;
    int change_atime = 0;
    int change_mtime = 0;
    int no_create = 0;
    struct utimbuf new_times;
    struct utimbuf *times = NULL;

    while ((opt = getopt(argc, argv, "amct:")) != -1) {
        switch (opt) {
            case 'a': change_atime = 1; break;
            case 'm': change_mtime = 1; break;
            case 'c': no_create = 1; break;
            case 't':
                if (parse_time_string(optarg, &new_times) != 0)
                    return 1;
                times = &new_times;
                break;
            default:
                fprintf(stderr, "사용법: %s [-a] [-m] [-c] [-t time] 파일...\n", argv[0]);
                return 1;
        }
    }

    if (!change_atime && !change_mtime) {
        // 아무 옵션도 없으면 둘 다 변경
        change_atime = change_mtime = 1;
    }

    for (int i = optind; i < argc; i++) {
        const char *filename = argv[i];
        int exists = access(filename, F_OK) == 0;

        if (!exists && !no_create) {
            int fd = open(filename, O_CREAT | O_WRONLY, 0666);
            if (fd < 0) {
                perror("파일 생성 실패");
                continue;
            }
            close(fd);
        }

        if (exists || !no_create) {
            struct stat st;
            if (stat(filename, &st) < 0) {
                perror("stat 실패");
                continue;
            }

            struct utimbuf current;
            if (!times) {
                time_t now = time(NULL);
                current.actime = st.st_atime;
                current.modtime = st.st_mtime;
                if (change_atime) current.actime = now;
                if (change_mtime) current.modtime = now;
                times = &current;
            } else if (!(change_atime && change_mtime)) {
                // 지정된 시간에서 atime, mtime 중 하나만 변경
                if (!change_atime) times->actime = st.st_atime;
                if (!change_mtime) times->modtime = st.st_mtime;
            }

            if (utime(filename, times) < 0) {
                perror("시간 설정 실패");
            }
        }
    }

    return 0;
}

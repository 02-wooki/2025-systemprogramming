#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>

// 디렉토리가 비어 있는지 확인
int is_directory_empty(const char *dirname) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) return 0;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        // 무시할 기본 항목 . ..
        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
            count++;
    }

    closedir(dir);
    return count == 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory> [<directory> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        struct stat st;

        if (stat(argv[i], &st) != 0) {
            perror(argv[i]);
            continue;
        }

        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "rmdir: %s: Not a directory\n", argv[i]);
            continue;
        }

        if (!is_directory_empty(argv[i])) {
            fprintf(stderr, "rmdir: %s: Directory not empty\n", argv[i]);
            continue;
        }

        if (rmdir(argv[i]) != 0) {
            perror(argv[i]);
            continue;
        }
    }

    return 0;
}

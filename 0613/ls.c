#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

#define MAX_ENTRIES 1024

// 옵션 플래그
bool opt_a=false,opt_A=false,opt_l=false,opt_h=false,opt_S=false;
bool opt_t=false,opt_r=false,opt_b=false,opt_i=false,opt_L=false;
bool opt_m=false,opt_R=false;

// 파일 정보 구조체
typedef struct {
    char name[256];
    char path[512];
    struct stat st;
} FileEntry;

FileEntry entries[MAX_ENTRIES];
int entry_count = 0;

void parse_options(int argc, char *argv[], int *start) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            *start = i;
            return;
        }
        for (int j = 1; argv[i][j]; j++) {
            switch (argv[i][j]) {
                case 'a': opt_a = true; break;
                case 'A': opt_A = true; break;
                case 'l': opt_l = true; break;
                case 'h': opt_h = true; break;
                case 'S': opt_S = true; break;
                case 't': opt_t = true; break;
                case 'r': opt_r = true; break;
                case 'b': opt_b = true; break;
                case 'i': opt_i = true; break;
                case 'L': opt_L = true; break;
                case 'm': opt_m = true; break;
                default:
                    fprintf(stderr, "ls: invalid option -- '%c'\n", argv[i][j]);
                    exit(1);
            }
        }
    }
    *start = argc;
}

int compare_entries(const void *a, const void *b) {
    FileEntry *fa = (FileEntry*)a;
    FileEntry *fb = (FileEntry*)b;

    int result = 0;
    if (opt_S) {
        result = fb->st.st_size - fa->st.st_size;
    } else if (opt_t) {
        result = fb->st.st_mtime - fa->st.st_mtime;
    } else {
        result = strcmp(fa->name, fb->name);
    }

    return opt_r ? -result : result;
}

void human_readable(off_t size) {
    const char *units = "BKMGT";
    double s = size;
    int i = 0;
    while (s >= 1024 && i < 4) {
        s /= 1024;
        i++;
    }
    printf("%4.1f%c ", s, units[i]);
}

void escape_nonprint(const char *s) {
    for (int i = 0; s[i]; i++) {
        if ((unsigned char)s[i] < 32 || s[i] == 127) {
            printf("^%c", s[i] + 64);
        } else {
            putchar(s[i]);
        }
    }
}

void print_entries() {
    qsort(entries, entry_count, sizeof(FileEntry), compare_entries);

    for (int i = 0; i < entry_count; i++) {
        FileEntry *f = &entries[i];

        if (opt_i) printf("%8lu ", f->st.st_ino);

        if (opt_l) {
            char perms[11] = "----------";
            if (S_ISDIR(f->st.st_mode)) perms[0] = 'd';
            if (S_ISLNK(f->st.st_mode)) perms[0] = 'l';
            if (f->st.st_mode & S_IRUSR) perms[1] = 'r';
            if (f->st.st_mode & S_IWUSR) perms[2] = 'w';
            if (f->st.st_mode & S_IXUSR) perms[3] = 'x';
            if (f->st.st_mode & S_IRGRP) perms[4] = 'r';
            if (f->st.st_mode & S_IWGRP) perms[5] = 'w';
            if (f->st.st_mode & S_IXGRP) perms[6] = 'x';
            if (f->st.st_mode & S_IROTH) perms[7] = 'r';
            if (f->st.st_mode & S_IWOTH) perms[8] = 'w';
            if (f->st.st_mode & S_IXOTH) perms[9] = 'x';

            struct passwd *pw = getpwuid(f->st.st_uid);
            struct group  *gr = getgrgid(f->st.st_gid);
            char timebuf[64];
            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&f->st.st_mtime));

            printf("%s %3lu %-8s %-8s ", perms, f->st.st_nlink, pw->pw_name, gr->gr_name);
            if (opt_h)
                human_readable(f->st.st_size);
            else
                printf("%8ld ", f->st.st_size);
            printf("%s ", timebuf);
        }

        if (opt_b)
            escape_nonprint(f->name);
        else
            printf("%s", f->name);

        if (opt_l && S_ISLNK(f->st.st_mode)) {
            char link_target[256];
            ssize_t len = readlink(f->path, link_target, sizeof(link_target) - 1);
            if (len >= 0) {
                link_target[len] = '\0';
                printf(" -> %s", link_target);
            }
        }

        printf(opt_m ? ", " : "\n");
    }
    if (opt_m) printf("\n");
}

void list_dir(const char *dir) {
    DIR *dp = opendir(dir);
    if (!dp) {
        perror(dir);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL) {
        if (!opt_a && entry->d_name[0] == '.') continue;
        if (opt_A && (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))) continue;

        snprintf(entries[entry_count].name, sizeof(entries[entry_count].name), "%s", entry->d_name);
        snprintf(entries[entry_count].path, sizeof(entries[entry_count].path), "%s/%s", dir, entry->d_name);
        (opt_L ? stat : lstat)(entries[entry_count].path, &entries[entry_count].st);

        entry_count++;
        if (entry_count >= MAX_ENTRIES) break;
    }
    closedir(dp);
    print_entries();
}

int main(int argc, char *argv[]) {
    int target_start = 1;
    parse_options(argc, argv, &target_start);  // 옵션 파싱

    if (target_start == argc) {
        // 인자가 없는 경우 현재 디렉토리 출력
        list_dir(".");
    } else {
        bool multiple = (argc - target_start) > 1;
        for (int i = target_start; i < argc; ++i) {
            if (multiple)
                printf("%s:\n", argv[i]);

            list_dir(argv[i]);

            if (multiple && i < argc - 1)
                printf("\n");
        }
    }

    return 0;
}


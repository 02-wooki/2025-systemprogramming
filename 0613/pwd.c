#include <stdio.h>
#include <sys/syslimits.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char path[PATH_MAX];
    getcwd(path, sizeof(path));
    printf("%s\n", path);
    exit(0);
}

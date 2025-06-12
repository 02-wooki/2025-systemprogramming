#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("uid=%d(%s) gid=%d\n", getuid(), getlogin(), getgid());
    exit(0);
}

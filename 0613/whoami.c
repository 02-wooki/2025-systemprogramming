#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    printf("%s\n", getlogin());
    exit(0);
}
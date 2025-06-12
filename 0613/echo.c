#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

char *subString(char *input, int begin, int end) {
    char *str = (char*)malloc((end - begin) + 2);
    for (int i = begin; i < end; ++i)
        str[i - begin] = input[i];
    str[end - begin] = '\0';
    return str;
}

int main(int argc, char* argv[]) {
    if (argc <= 1)
        exit(0);

    // -n 옵션
    bool option_n = false;

    if (!strcmp(argv[1], "-n"))
        option_n = true;

    for (int i = 1; i < argc; i++) {
        bool space = true;
        if (option_n && i == 1)
            continue;
        if (argv[i][0] == '$') {
            char *env = getenv(subString(argv[i], 1, strlen(argv[i])));
            argv[i] = env == NULL ? "" : env;
            space = (env != NULL);
        }
        printf("%s%s", argv[i], space ? " " : "");
    }

    if (!option_n)
        printf("\n");

    exit(0);
}
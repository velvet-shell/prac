#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {
    int cnt = atoi(argv[1]);
    for (int i = 2; i < cnt && i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        char str[PATH_MAX];
        fgets(str, PATH_MAX, f);
        if (str[strlen(str) - 1] == '\n') {
            str[strlen(str) - 1] == 0;
        }
        if (!fork) {
            execlp();
        }
    }
    return 0;
}

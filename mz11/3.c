#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>

void son(const char *cmd) {
    FILE *f = fopen(cmd, "r");
    char str[PATH_MAX];
    fgets(str, PATH_MAX, f);
    fclose(f);
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = 0;
    }
    int pid = fork();
    if (pid == -1) {
        _exit(1);
    }
    if (!pid) {
        execlp(str, str, NULL);
        _exit(1);
    }
}

void wait_check(int *success) {
    int status;
    while (wait(&status) != -1) {
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            (*success)++;
        }
    }
}

int main(int argc, char *argv[]) {
    int cnt = atoi(argv[1]);
    int i = 2;
    for (; i < cnt + 2 && i < argc; i++) {
        son(argv[i]);
    }
    int success = 0;
    wait_check(&success);
    for (; i < argc; i++) {
        son(argv[i]); 
        wait_check(&success); 
    }
    printf("%d\n", success);
    return 0;
}

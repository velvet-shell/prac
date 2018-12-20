#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 0;
    }
    int fd24[2];
    pipe(fd24);
    if (!fork()) {
        close(fd24[0]);
        int fd12[2];
        pipe(fd12);
        if (!fork()) {
            close(fd12[1]);
            dup2(fd12[0], 0);
            dup2(fd24[1], 1);
            close(fd12[0]);
            close(fd24[1]);
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        }
        close(fd24[1]);
        close(fd12[0]);
        dup2(fd12[1], 1);
        close(fd12[1]);
        int modulo = atoi(argv[2]);
        int count = atoi(argv[1]);
        for (int i = 1; i <= count; i++) {
            unsigned long long tmp = i % modulo;
            tmp *= tmp;
            tmp = tmp % modulo;
            printf("%u ", (unsigned) tmp);
            fflush(stdout);
        }
        close(1);
        wait(NULL);
        return 0;
    }
    close(fd24[1]);
    if (!fork()) {
        if (!fork()) {
            dup2(fd24[0], 0);
            close(fd24[0]);
            int c;
            while (scanf("%d", &c) == 1) {
                printf("%d\n", c);
                fflush(stdout);
            }
            return 0;
        }
        close(fd24[0]);
        wait(NULL);
        return 0;
    }
    close(fd24[0]);
    while (wait(NULL) != -1);
    printf("0\n");
    fflush(stdout);
    return 0;
}

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    int fd[2];
    pipe(fd);
    if (!fork()) {
        if (!fork()) {
            close(fd[1]);
            long long sum = 0;
            int tmp;
            while (1) {
                char c = 0;
                for (int i = 0; i < sizeof(tmp); i++) {
                    if (!read(fd[0], &c, 1)) {
                        break;
                    }
                    tmp = c;
                    c <<= CHAR_BIT;
                }
                sum += tmp;
            }
            printf("%lld\n", sum);
            fflush(stdout);
            return 0;
        } else {
            close(fd[1]);
            close(fd[0]);
            wait(NULL);
            return 0;
        }
    } else {
        close(fd[0]);
        int tmp;
        while (scanf("%d", &tmp) == 1) {
            for (int i = 0; i < sizeof(tmp); i++) {
                char c = tmp & 0xFF;
                c >>= CHAR_BIT;
                write(fd[1], &c, 1);
            }
        }
        close(fd[1]);
        wait(NULL);
        return 0;
    }
}

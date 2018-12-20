#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    int fd[2];
    pipe(fd);
    if (!fork()) {
        if (!fork()) {
            close(fd[1]);
            long long sum = 0;
            int tmp;
            while (read(fd[0], &tmp, sizeof(tmp)) == sizeof(tmp)) {
                sum += tmp;
            }
            printf("%lld\n", sum);
            fflush(stdout);
            close(fd[0]);
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
            if (write(fd[1], &tmp, sizeof(tmp)) != sizeof(tmp)) {
                return 1;
            }
        }
        close(fd[1]);
        wait(NULL);
        return 0;
    }
}

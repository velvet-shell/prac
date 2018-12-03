#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int fd[2];
    pipe(fd);
    if (!fork()) {
        if (!fork()) {
            if (!fork()) {
                close(fd[0]);
                time_t c_time = time(NULL);
                write(fd[1], &c_time, sizeof(c_time));
                write(fd[1], &c_time, sizeof(c_time));
                write(fd[1], &c_time, sizeof(c_time));
                return 0;
            } else {
                wait(NULL);
                close(fd[1]);
                time_t c_time;
                read(fd[0], &c_time, sizeof(c_time));
                struct tm tmp;
                localtime_r(&c_time, &tmp);
                printf("D:%d\n", tmp.tm_mday);
                fflush(stdout);
                return 0;
            }
        } else {
            wait(NULL);
            close(fd[1]);
            time_t c_time;
            read(fd[0], &c_time, sizeof(c_time));
            struct tm tmp;
            localtime_r(&c_time, &tmp);
            printf("M:%d\n", tmp.tm_mon + 1);
            fflush(stdout);
            return 0;
        }
    } else {
        wait(NULL);
        close(fd[1]);
        time_t c_time;
        read(fd[0], &c_time, sizeof(c_time));
        struct tm tmp;
        localtime_r(&c_time, &tmp);
        printf("Y:%d\n", tmp.tm_year + 1900);
        fflush(stdout);
        return 0;
    }
}

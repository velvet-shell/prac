#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

struct tm* gettime(int fd[2])
{
    wait(NULL);
    close(fd[1]);
    time_t c_time;
    read(fd[0], &c_time, sizeof(c_time));
    return localtime(&c_time);    
}

int main(void) {
    int fd[2];
    pipe(fd);
    if (!fork()) {
        if (!fork()) {
            if (!fork()) {
                close(fd[0]);
                time_t c_time = time(NULL);
                for (int i = 0; i < 3; i++) {
                    write(fd[1], &c_time, sizeof(c_time));
                }
                return 0;
            } else {
                printf("D:%d\n", gettime(fd)->tm_mday);
                fflush(stdout);
                return 0;
            }
        } else {
            printf("M:%d\n", gettime(fd)->tm_mon + 1);
            fflush(stdout);
            return 0;
        }
    } else {
        printf("Y:%d\n", gettime(fd)->tm_year + 1900);
        fflush(stdout);
        return 0;
    }
}

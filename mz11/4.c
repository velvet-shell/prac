#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

FILE *out, *in;
int max;

void son(int id, void (*sig)(int)) {
    signal(SIGUSR1, sig);
    int num, pid;
    fscanf(in, "%d %d", &num, &pid);
    if (num == max) {
        fprintf(out, "%d\n", pid);
        fflush(out);
        _exit(0);
    }
    printf("%d %d\n", id, num++);
    fflush(stdout);
    fprintf(out, "%d %d\n", num, getpid());
    fflush(out);
    kill(pid, SIGUSR1);
}

void sig1(int sig) {
    son(1, sig1);
}

void sig2(int sig) {
    son(2, sig2);
}

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);

    out = fdopen(fd[1], "w");
    in = fdopen(fd[0], "r");

    max = atoi(argv[1]);
    int pid1 = fork();
    if (!pid1) {
        signal(SIGUSR1, sig1);
        while(1) {
            pause();
        }
    }
    int pid2 = fork();
    if (!pid2) {
        signal(SIGUSR1, sig2);
        while(1) {
            pause();
        }
    }
    fprintf(out, "%d %d\n", 1, pid2);
    fflush(out);
    kill(pid1, SIGUSR1);

    wait(NULL);
    int pid;
    fscanf(in, "%d", &pid);
    fprintf(out, "%d %d\n", max, pid);
    fflush(out);
    kill(pid, SIGUSR1); 
    wait(NULL);

    close(fd[1]);
    close(fd[0]);

    printf("Done\n");
    fflush(stdout);
    return 0;
}

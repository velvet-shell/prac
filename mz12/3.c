#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

enum
{
    INC = 5,
    DEC = 4
};

volatile int f = 0;

void up(int sig) {
    f = 1;
}

void down(int sig) {
    f = 2;
}

int main(int argc, char *argv[]) {
    sigset_t sigset, oldmask;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigaddset(&sigset, SIGUSR2);
    sigprocmask(SIG_BLOCK, &sigset, &oldmask);

    struct sigaction sig1 = { 0 };
    struct sigaction sig2 = { 0 };
    sig1.sa_handler = up;
    sig2.sa_handler = down;
    sigaction(SIGUSR1, &sig1, NULL);
    sigaction(SIGUSR2, &sig2, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int cnt = 0;
    while (1) {
        sigsuspend(&oldmask);
        if (f == 1) {
            cnt += INC;
            printf("%d %d\n", SIGUSR1, cnt);
        } else if (f == 2) {
            cnt -= DEC;
            printf("%d %d\n", SIGUSR2, cnt);
        }
        fflush(stdout);
        if (cnt < 0) {
            return 0;
        }
    } 
    return 0;
}

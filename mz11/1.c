#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

enum
{
    MAX_SIGNALS = 6
};

volatile int i = 0;

void f(int sig)
{
    signal(SIGHUP, f);
    if (i < MAX_SIGNALS - 1) {
        printf("%d\n", i);
        i++;
        fflush(stdout);
    } else {
        exit(0);
    }
}

int main(void) {
    signal(SIGHUP, f);
    printf("%d\n", getpid());
    fflush(stdout);
    while(1) {
        pause();
    }
    return 0;
}

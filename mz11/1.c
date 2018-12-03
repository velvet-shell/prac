#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

volatile int i = 0;

void f(int sig)
{
    signal(SIGHUP, f);
    if (i < 5) {
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

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

enum
{
    SUM_MODE = 0,
    MUL_MODE = 1
};

volatile int flag = 0;

void sum(int sig)
{
    signal(SIGINT, sum);
    flag = SUM_MODE;
}

void mul(int sig)
{
    signal(SIGQUIT, mul);
    flag = MUL_MODE;
}

int main(void) {
    signal(SIGINT, sum);
    signal(SIGQUIT, mul);

    printf("%d\n", getpid());
    fflush(stdout);

    int tmp;
    int sum = 0;
    while (scanf("%d", &tmp) == 1) {
        if (flag == SUM_MODE) {
            sum += (long long) tmp;
        } else {
            sum *= (long long) tmp;
        }
        printf("%d\n", sum);
        fflush(stdout);
    }
    return 0;
}

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

volatile int prime = 0, cnt = 0;

void sig1(int sig) {
    signal(SIGINT, sig1);
    if (cnt < 3) {
        printf("%d\n", prime);
        fflush(stdout);
        cnt++;
    } else {
        exit(0);
    }
}

void sig2(int sig) {
    exit(0);
}

int main(void) {
    int low, high;
    scanf("%d%d", &low, &high);

    printf("%d\n", getpid());
    fflush(stdout);

    signal(SIGINT, sig1);
    signal(SIGTERM, sig2);

    if (low < 2) {
        low = 2;
    }
    for (int i = low; i < high; i++) {
        int is_prime = 1;
        for (int j = 2; j * j < i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            prime = i;
        }
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}

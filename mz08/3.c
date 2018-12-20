#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

enum
{
    LENGTH = 8, //string length
    SONS = 3 //number of sons
};

int main(void)
{
    for (int i = 1; i <= SONS; i++) {
        if (!fork()) {
            char buf[LENGTH] = {};
            read(0, buf, LENGTH);
            int a = atoi(buf);
            printf("%d %d\n", i, a * a);
            fflush(stdout);
            return 0;
        }
    }
    while(wait(NULL) != -1);
    return 0;
}

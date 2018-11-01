#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    for (int i = 1; i < 4; i++) {
        if (!fork()) {
            char buf[8] = {};
            read(0, buf, 8);
            int a = atoi(buf);
            printf("%d %d\n", i, a * a);
            fflush(stdout);
            return 0;
        }
    }
    while(wait(NULL) != -1);
    return 0;
}

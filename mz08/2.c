#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    if (!fork()) {
        if (!fork()) {
            printf("3 ");
        } else {
            wait(NULL);
            printf("2 ");
        }
    } else {
        wait(NULL);
        printf("1\n");
    }
    return 0;
}

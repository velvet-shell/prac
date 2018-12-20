#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void son(int *wpipe, int *rpipe, int id, int max)
{
    close(wpipe[0]);
    close(rpipe[1]);
    FILE *out = fdopen(wpipe[1], "w");
    FILE *in = fdopen(rpipe[0], "r");
    int num;
    fflush(in);
    while (fscanf(in, "%d", &num) == 1 && num != max) {
        printf("%d %d\n", id, num++);
        fflush(stdout);
        if (num >= max) {
            _exit(0); 
        }
        fprintf(out, "%d\n", num);
        fflush(out);
    }
    fclose(out);
    fclose(in);
    _exit(0);
}

int main(int argc, char *argv[])
{
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    FILE *start = fdopen(fd2[1], "w");
    fprintf(start, "1\n");
    fflush(start);
    int max = atoi(argv[1]);

    if (!fork()) {
        son(fd1, fd2, 1, max);
    }
    if (!fork()) {
        son(fd2, fd1, 2, max);
    }
    close(fd1[1]);
    close(fd2[1]);
    close(fd2[0]);
    close(fd1[0]);
    while(wait(NULL) != -1);
    printf("Done\n");
    fflush(stdout);
    fclose(start);
    return 0;
}

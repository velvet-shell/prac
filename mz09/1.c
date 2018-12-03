#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

enum { ERRCODE = 42 };

int main(int argc, char *argv[])
{
    if (argc != 5) {
        return 0;
    }
    if (!fork()) {
        int fd1, fd2, fd3;
        fd1 = open(argv[2], O_RDONLY);
        fd2 = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, 0660);
        fd3 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0660);
        if (fd1 < 0 || fd2 < 0 || fd3 < 0) {
            return ERRCODE;
        }
        if (dup2(fd1, 0) < 0) {
            return ERRCODE;
        }
        if (dup2(fd2, 1) < 0) {
            return ERRCODE;
        }
        if (dup2(fd3, 2) < 0) {
            return ERRCODE;
        }
        execlp(argv[1], argv[1], NULL);
        return ERRCODE;
    } else {
        int status;
        wait(&status);
        printf("%d\n", status);
    }
    return 0;
}

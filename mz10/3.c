#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 6) {
        return 1;
    }
    int fd[2];
    pipe(fd);
    if (!fork()) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        if (!fork()) {
            int file1 = open(argv[4], O_RDONLY);
            if (file1 < 0) {
                _exit(1);
            }
            dup2(file1, 0);
            close(file1);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        } else {
            int status;
            wait(&status);
            if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                if (!fork()) {
                    execlp(argv[2], argv[2], NULL);
                    _exit(1);
                } else {
                    wait(NULL);
                }
            }
            return 0;
        }
    } else {
        if (!fork()) {
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            int file2 = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0666);
            if (file2 < 0) {
                return 1;
            }
            dup2(file2, 1);
            close(file2);
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        } else {
            close(fd[1]);
            close(fd[0]);
            while(wait(NULL) != -1);
        }
        return 0;
    }
}

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int fd[2];
    pipe(fd);
    if (!fork()) {
        close(fd[0]);
        if (!fork()) {
            int fd1 = open(argv[5], O_RDONLY);
            dup2(fd[1], 1);
            dup2(fd1, 0);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        } else {
            int status;
            wait(&status);
            if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                if (!fork()) {
                    dup2(fd[1], 1);
                    execlp(argv[2], argv[2], NULL);
                    _exit(1);
                } else {
                    wait(NULL);
                }
            }
            return 0;
        }
    } else {
        close(fd[1]);
        dup2(fd[0], 0);
        int fd2 = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0660);
        dup2(fd2, 1);
        pid_t pid = fork();
        if (!pid) {
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        } else {
            waitpid(pid, NULL, 0);
        }
        wait(NULL);
    }
    return 0;
}

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int mysys(const char *str) {
    int pid = fork();
    if (pid == -1) {
        return -1;
    }
    if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            return 128 + WTERMSIG(status);
        } else {
            return WEXITSTATUS(status);
        }
    }
}

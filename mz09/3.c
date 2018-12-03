#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int run_proc(char const *str) {
    if (!fork()) {
        execlp(str, str, NULL);
        return 1;
    } else {
        int status;
        wait(&status);
        return WIFEXITED(status) && !WEXITSTATUS(status);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }
    return !((run_proc(argv[1]) || run_proc(argv[2])) && run_proc(argv[3]));
}

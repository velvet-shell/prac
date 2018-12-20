#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

volatile int mode = 3;

void zero(int sig) {
    mode = 0;
}

void one(int sig) {
    mode = 1;
}

void stop(int sig) {
    mode = 2; 
}

void empty(int sig) {
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    sigaction(SIGALRM, &(struct sigaction) { 
            .sa_handler = empty, .sa_flags = SA_RESTART }, NULL);

    int pid1 = fork();
    if (!pid1) {

        sigset_t mask, oldmask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGUSR1);
        sigaddset(&mask, SIGUSR2);
        sigaddset(&mask, SIGALRM);
        sigaddset(&mask, SIGIO);
        sigprocmask(SIG_BLOCK, &mask, &oldmask);
        sigaddset(&oldmask, SIGALRM);

        sigaction(SIGUSR1, &(struct sigaction) { 
                .sa_handler = zero, .sa_flags = SA_RESTART }, NULL);
        sigaction(SIGUSR2, &(struct sigaction) {
                .sa_handler = one, .sa_flags = SA_RESTART }, NULL);
        sigaction(SIGIO, &(struct sigaction) {
                .sa_handler = stop, .sa_flags = SA_RESTART }, NULL);

        char c = 0;
        int offset = 0;
        while (1) {
            kill(0, SIGALRM);
            sigsuspend(&oldmask);
            if (offset == CHAR_BIT) {
                write(1, &c, 1);
                c = 0;
                offset = 0;
            }
            if (mode == 2) {
                return 0;     
            }
            if (mode) {
                c |= 1 << offset;
            }
            offset++;
        }
    }

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);

    if (!fork()) {
        int fd = open(argv[1], O_RDONLY);
        if (fd < 0) {
            return 1;
        }
        char c;
        while (read(fd, &c, sizeof(c)) == sizeof(c)) {
            for (int i = 0; i < CHAR_BIT; i++) {
                sigsuspend(&oldmask);
                if (c & 1) {
                    kill(pid1, SIGUSR2);
                } else {
                    kill(pid1, SIGUSR1);
                }
                c >>= 1;
            }
        }
        close(fd);
        kill(pid1, SIGIO);
        return 0;
    }
    while(wait(NULL) != -1);
    return 0;
}

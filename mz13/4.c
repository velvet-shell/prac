#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    int count = atoi(argv[1]);
    
    key_t key = ftok("up13-4", 's');
    int semid = semget(key, count, IPC_CREAT | 0666);

    setvbuf(stdin, NULL, _IONBF, 0);
    for (int i = 0; i < count; i++) {
        if (!fork()) {
            struct sembuf pi = {i, -1, SEM_UNDO};
            while (1) {
                if (semop(semid, &pi, 1) < 0) {
                    return 0;
                }
                int a;
                if (scanf("%d", &a) == 1) {
                    printf("%d %d\n", i, a);
                    fflush(stdout);
                    int nextid = (a % count + count) % count;
                    struct sembuf vnext = {nextid, 1, SEM_UNDO};
                    semop(semid, &vnext, 1);
                } else {
                    return 0;
                }
            }
        }
    }
    struct sembuf v0 = {0, 1, SEM_UNDO};
    semop(semid, &v0, 1);
    wait(NULL);
    semctl(semid, 0, IPC_RMID, 0);
    while (wait(NULL) != -1);
    return 0;
}

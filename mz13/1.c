#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int nproc = atoi(argv[1]);
    int key = atoi(argv[2]);
    int maxval = atoi(argv[3]);
    int semid = semget(key, nproc, IPC_CREAT | 0666);
    int shmid = shmget(key, 2 * sizeof(int), IPC_CREAT | 0666);
    int *shm = shmat(shmid, NULL, 0);
    struct sembuf v1 = {0, 1, SEM_UNDO};
    semop(semid, &v1, 1);
    shm[0] = 0;
    shm[1] = 0;
    for (int i = 0; i < nproc; i++) {
        if (!fork()) {
            struct sembuf pi = {i, -1, SEM_UNDO};
            while (1) {
                if (semop(semid, &pi, 1) < 0) {
                    return 0;
                }

                printf("%d %d %d\n", i + 1, shm[0], shm[1]);
                fflush(stdout);

                shm[0]++;
                shm[1] = i + 1;

                if (shm[0] <= maxval) {
                    int val = shm[0];
                    int nextid = (unsigned long long) (val % nproc) * (val % nproc) * (val % nproc)
                            * (val % nproc) % nproc;
                    struct sembuf vnext = {nextid, 1, SEM_UNDO};
                    semop(semid, &vnext, 1);
                } else {
                    return 0;
                }
            }
        }
    }
    wait(NULL);
    semctl(semid, 0, IPC_RMID, 0);
    while(wait(NULL) != -1);
    shmdt(shm);
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}

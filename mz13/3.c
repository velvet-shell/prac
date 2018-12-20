#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 6) {
        return 0;
    }

    int key = atoi(argv[1]);
    int n = atoi(argv[2]);
    long long value1 = atoi(argv[3]);
    long long value2 = atoi(argv[4]);
    long long maxval = atoi(argv[5]);
    if (maxval < 0) {
        maxval = -maxval;
    }

    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        return 1;
    }

    struct st {
        long type;
        long long x1;
        long long x2;
    };
    struct st buf;

    for (int i = 0; i < n; i++) {
        int pid = fork();
        if (pid == -1) {
            msgctl(msgid, IPC_RMID, NULL);
            while (wait(NULL) != -1);
            return 1;
        }
        if (!pid) {
            long long tmp;
            while (1) {
                if (msgrcv(msgid, (void *) &buf, sizeof(buf) - sizeof(long), i + 1, 0) < 0) {
                    return 0;
                }
                tmp = buf.x1 + buf.x2;

                printf("%d %lld\n", i, tmp);
                fflush(stdout);

                if (tmp > maxval) {
                    return 0;
                }
                buf.x1 = buf.x2;
                buf.x2 = tmp;
                buf.type = tmp % n + 1;

                msgsnd(msgid, (void *) &buf, sizeof(buf) - sizeof(long), IPC_NOWAIT);
            }
        }
    }

    buf.type = 1;
    buf.x1 = value1;
    buf.x2 = value2;
    msgsnd(msgid, (void *) &buf, sizeof(buf) - sizeof(long), IPC_NOWAIT);
    
    wait(NULL);
    msgctl(msgid, IPC_RMID, NULL);

    while(wait(NULL) != -1);
    return 0;
}

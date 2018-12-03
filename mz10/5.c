

int main(int argc, char *argv[])
{
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    int cnt;
    if (!fork()) {
        close(fd1[0]);
        close(fd2[1]);

        cnt = 1;
        printf("1 %d\n", cnt++);

        write(fd1[1], &cnt, sizeof(cnt));

        while (read(fd2[0], &cnt, sizeof(cnt))) {

        }
    }

    if (!fork()) {
        close(fd1[1]);
        close(fd2[0]);

        read(fd1[0], &cnt, sizeof(cnt));



    }


    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

unsigned long long hash_function(unsigned long long);

int
main(int argc, char *argv[])
{
    if (argc != 4) {
        return 1;
    }
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0660);
    if (fd < 0) {
        return 1;
    }
    unsigned long long now = strtoll(argv[2], NULL, 16);
    unsigned long long count = strtoll(argv[3], NULL, 10);

    if (!count) {
        close(fd);
        return 0;
    }
    if (lseek(fd, sizeof(now) * (count - 1), SEEK_END) < 0) {
        close(fd);
        return 1;
    }
    if (write(fd, &now, sizeof(now)) != sizeof(now)) {
        close(fd);
        return 1;
    }

    for (int i = 0; i < count - 1; i++) {

        lseek(fd, -2 * (long) sizeof(now), SEEK_CUR);
        now = hash_function(now);
        if (write(fd, &now, sizeof(now)) != sizeof(now)) {
            close(fd);
            return 1;
        }
    }
    close(fd);
    return 0;
}
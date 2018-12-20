#include <stdio.h>
#include <endian.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }
    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        return 1;
    }
    int min_ind = 0;
    long long min;
    if (read(fd, &min, sizeof(min)) != sizeof(min)) {
        close(fd);
        return 0;
    }
    int i = 1;
    long long tmp;
    while (read(fd, &tmp, sizeof(tmp)) == sizeof(tmp)) {
        if (tmp < min) {
            min = tmp;
            min_ind = i;
        }
        i++;
    }
    if (lseek(fd, min_ind * sizeof(min), SEEK_SET) < 0) {
        close(fd);
        return 1;
    }
    if (min != LLONG_MIN) {
        min = -min;
    }
    if (write(fd, &min, sizeof(min)) != sizeof(min)) {
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

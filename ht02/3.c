#include <stdio.h>
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
    int fd = creat(argv[1], 0600);
    if (fd < 0) {
        return 1;
    }
    unsigned tmp;
    while (scanf("%u", &tmp) == 1) {
        char big_endian[sizeof(tmp)];
        for (int i = 0; i < sizeof(tmp); i++) {
            big_endian[sizeof(tmp) - i - 1] = tmp;
            tmp >>= CHAR_BIT;
        }
        if (write(fd, &big_endian, sizeof(big_endian)) != sizeof(big_endian)) {
            close(fd);
            return 1;
        }
    }
    close(fd);
    return 0;
}
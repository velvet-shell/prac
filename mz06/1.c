#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int
main(int argc, char const *argv[])
{
    unsigned long long sum = 0;
    for (int i = 1; i < argc; i++) {
        struct stat buf;
        if (!lstat(argv[i], &buf) && S_ISREG(buf.st_mode) && buf.st_nlink == 1) {
            sum += buf.st_size;
        }
    }
    printf("%llu\n", sum);
    return 0;
}
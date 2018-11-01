#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int
main(int argc, char const *argv[])
{
    DIR *d;
    if (argc != 2) {
        return 1;
    }
    if ((d = opendir(argv[1])) == NULL) {
        return 1;
    }
    struct dirent *entry;
    unsigned long long sum = 0;

    while ((entry = readdir(d))) {

        char path[PATH_MAX + 2];
        snprintf(path, PATH_MAX + 2, "%s/%s", argv[1], entry->d_name);

        struct stat buf;
        if (stat(path, &buf) < 0) {
            continue;
        }
        if (S_ISREG(buf.st_mode) && getuid() == buf.st_uid && entry->d_name[0] >= 'A'
                && entry->d_name[0] <= 'Z') {

            sum += buf.st_size;
        }
    }
    printf("%llu\n", sum);
    closedir(d);
    return 0;
}

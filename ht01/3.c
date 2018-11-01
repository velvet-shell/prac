#include <stdio.h>
#include <limits.h>
#include <string.h>

enum
{
    MAX_BUF = 65536, //size of read buffer
    BASE = 10   //base of input number system
};

void
print_result(const unsigned long long *arr)
{
    for (int i = 0; i < BASE; i++) {
        printf("%d %llu\n", i, arr[i]);
    }
    return;
}

int
main(void)
{
    char buf[PATH_MAX + 2];
    unsigned long long arr[BASE] = { 0 };

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        print_result(arr);
        return 0;
    }

    size_t length = strlen(buf);
    if (length >= 2 && (buf[length - 2] == '\r' || buf[length - 2] == '\n')) {
        buf[length - 2] = 0;
    }
    if (buf[length - 1] == '\r' || buf[length - 1] == '\n') {
        buf[length - 1] = 0;
    }

    FILE *fd = fopen(buf, "r");

    if (fd == NULL) {
        print_result(arr);
        return 0;
    }

    char tmp[MAX_BUF];
    while (fgets(tmp, sizeof(tmp), fd)) {
        for (int i = 0; tmp[i]; i++) {
            if (tmp[i] >= '0' && tmp[i] <= '9') {
                arr[tmp[i] - '0']++;
            }
        }
    }
    fclose(fd);
    print_result(arr);
    return 0;
}
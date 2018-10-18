#include <stdio.h>
#include <time.h>
#include <string.h>

enum
{
    D_SEC = 86400 //seconds in one day
};

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        return 1;
    }

    int year, day;
    sscanf(argv[1], "%d", &year);
    sscanf(argv[2], "%d", &day);

    struct tm time = { 0 };

    time.tm_isdst = -1;
    time.tm_year = year - 1900;
    time_t off = mktime(&time);
    off += day * D_SEC;
    localtime_r(&off, &time);

    if (!time.tm_wday) {
        time.tm_wday = 7;
    }

    printf("%d %d %d %d\n", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday, time.tm_wday);
    return 0;
}
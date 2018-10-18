#include <stdio.h>
#include <string.h>
#include <time.h>

int
main(int argc, char *argv[])
{
    FILE *f;
    if ((f = fopen(argv[1], "r")) == NULL) {
        return 1;
    }
    time_t prev, next;
    struct tm time;
    memset(&time, 0, sizeof(time));
    int year, mon;
    fscanf(f, "%d/%d/%d %d:%d:%d", &year, &mon, &time.tm_mday, &time.tm_hour, &time.tm_min, &time.tm_sec);
    time.tm_year = year - 1900;
    time.tm_mon = mon - 1;
    time.tm_isdst = -1;
    prev = mktime(&time);
    memset(&time, 0, sizeof(time));
    while (fscanf(f, "%d/%d/%d %d:%d:%d", &year, &mon, &time.tm_mday, &time.tm_hour, &time.tm_min, &time.tm_sec) == 6) {
        time.tm_year = year - 1900;
        time.tm_mon = mon - 1;

        time.tm_isdst = -1;
        next = mktime(&time);
        printf("%ld\n", next - prev);
        prev = next;
        memset(&time, 0, sizeof(time));
    }
    return 0;
}
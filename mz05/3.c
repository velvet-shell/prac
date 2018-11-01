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
    struct tm time = { 0 };
    time_t prev, next;
    int year, mon;
    int first_iteration = 1;

    while (fscanf(f, "%d/%d/%d %d:%d:%d", &year, &mon, &time.tm_mday, &time.tm_hour, &time.tm_min,
            &time.tm_sec) == 6) {

        time.tm_year = year - 1900;
        time.tm_mon = mon - 1;
        time.tm_isdst = -1;

        next = mktime(&time);

        if (!first_iteration) {
            printf("%ld\n", next - prev);
        }

        first_iteration = 0;
        prev = next;
        memset(&time, 0, sizeof(time));
    }
    return 0;
}
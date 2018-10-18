#include <stdio.h>
#include <time.h>
#include <string.h>

int
main(void)
{
    struct tm gregorian = { 0 };

    gregorian.tm_year = 25;
    gregorian.tm_mon = 9;
    gregorian.tm_mday = 7;
    gregorian.tm_isdst = -1;

    long long offset = mktime(&gregorian);

    int year, month, day;
    while (scanf("%d%d%d", &year, &month, &day) == 3) {
        memset(&gregorian, 0, sizeof(gregorian));

        gregorian.tm_year = year - 1900;
        gregorian.tm_mon = month - 1;
        gregorian.tm_mday = day;
        gregorian.tm_isdst = -1;

        long long time = mktime(&gregorian);

        time -= offset;
        time /= (3600 * 24);

        unsigned long long nday = time % 30 + 1;
        unsigned long long nmon = (time / 30) % 12 + 1;
        unsigned long long nyear = time / 360 + 1;

        printf("%llu %llu %llu\n", nyear, nmon, nday);
    }
    return 0;
}
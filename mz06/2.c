#include <stdio.h>
#include <time.h>
#include <string.h>

enum
{
    BDAY_YEAR = 25, //Emperor's birthday according to the gregorian calendar
    BDAY_MON = 9,
    BDAY_MDAY = 7,
    YDAYS = 360, //days in 1 year
    YMONS = 12, //months in 1 year
    MDAYS = 30, //days in 1 month
    DSECS = 86400 //seconds in 1 day
};

int
main(void)
{
    struct tm gregorian = { 0 };

    gregorian.tm_year = BDAY_YEAR;
    gregorian.tm_mon = BDAY_MON;
    gregorian.tm_mday = BDAY_MDAY;
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
        time /= DSECS;

        unsigned long long nday = time % MDAYS + 1;
        unsigned long long nmon = (time / MDAYS) % YMONS + 1;
        unsigned long long nyear = time / YDAYS + 1;

        printf("%llu %llu %llu\n", nyear, nmon, nday);
    }
    return 0;
}

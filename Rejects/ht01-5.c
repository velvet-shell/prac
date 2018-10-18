#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

char *getline2(FILE *f);

enum
{
    BAD_INPUT = 0xbedabeda,
    EMPTY_INPUT = 0x0bad1dea,
    BASE = 10
};

int
main(void)
{
    int line_num = 1;
    char *str;
    while ((str = getline2(stdin))) {
        char *now = str;
        unsigned sum = 0;
        int num_cnt = 0;

        while (*now != '\n' && *now) {

            if (isdigit((unsigned char) *now)
                    || ((*now == '-' || *now == '+') && isdigit((unsigned char) *(now + 1)))) {

                num_cnt++;
                long converted = strtol(now, &now, BASE);

                if (errno == ERANGE || converted > INT_MAX || converted < INT_MIN) {
                    sum += (converted > 0) ? num_cnt : -num_cnt;
                    errno = 0;
                } else {
                    sum += converted;
                }

            } else if (isspace((unsigned char) *now)) {
                now++;
            } else {
                break;
            }
        }

        if (*now != '\n' && *now) {
            printf("%d\n", BAD_INPUT + line_num);
        } else if (!num_cnt) {
            printf("%d\n", EMPTY_INPUT + line_num);
        } else {
            printf("%d\n", (int) sum);
        }

        line_num++;
        free(str);
    }
    return 0;
}
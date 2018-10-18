#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h>

enum
{
    READ_SIZE = 4,
    BASE = 10
};

int
main(void)
{
    unsigned char buf[READ_SIZE];
    uint64_t sum = 0;
    uint64_t tmp = 0;
    char neg = 0;
    int read_cnt;
    while ((read_cnt = read(STDIN_FILENO, buf, READ_SIZE))) {
        if (tmp && isspace(buf[0])) {
            if (neg) {
                sum -= tmp;
            } else {
                sum += tmp;
            }
            neg = 0;
        }
        for (int i = 0; i < read_cnt; i++) {
            if (buf[i] == '-') {
                neg = 1;

            } else if (isdigit(buf[i])) {
                tmp = tmp * BASE + buf[i] - '0';

            } else if (i && isspace(buf[i]) && isdigit(buf[i - 1])) {
                if (neg) {
                    sum -= tmp;
                } else {
                    sum += tmp;
                }
                tmp = 0;
                neg = 0;
            }
        }
    }
    if (neg) {
        sum -= tmp;
    } else {
        sum += tmp;
    }
    printf("%" PRId64 "\n", (int64_t) sum);
    return 0;
}
#include <stdio.h>
#include <math.h>

enum
{
    ROUND_PRECISION = 10000,
    MAX_RATE_VALUE = 10000, //максимально допустимый курс
    MIN_RATE_VALUE = 0, //минимально допустимый курс
    MAX_RATE_CHANGE = 100, //максимальное изменение за день в процентах
    MIN_RATE_CHANGE = -100 //минимальное изменение за день в процентах
};
//ROUND_PRECISION константа для округления с точностью до (x) знаков после запятой, равная (10 ^ x)

int
main(int argc, char* argv[])
{
    if (argc == 1) {
        return 1;
    }
    double rate;
    if (sscanf(argv[1], "%lf", &rate) != 1) {
        return 1;
    }
    if (rate <= MIN_RATE_VALUE || rate > MAX_RATE_VALUE) {
        return 1;
    }
    for (int i = 2; i < argc; i++) {
        double tmp;
        if (sscanf(argv[i], "%lf", &tmp) != 1) {
            return 1;
        }
        if (tmp <= MIN_RATE_CHANGE || tmp >= MAX_RATE_CHANGE) {
            return 1;
        }
        rate += rate * (tmp / 100);
        rate = round(rate * ROUND_PRECISION) / ROUND_PRECISION;
        if (rate <= MIN_RATE_VALUE || rate > MAX_RATE_VALUE) {
            return 1;
        }
    }
    printf("%.4lf\n", rate);
    return 0;
}
#include <stdio.h>
#include <stdint.h>

int
main(void)
{
    int n, w;
    if (scanf("%o%o", &n, &w) != 2) {
        return 1;
    }
    uint32_t rows = 1 << n;
    uint32_t j = 0;
    for (uint32_t i = 0; i < rows; i++) {
        if (i < rows / 2) {
            printf("|%*o|%*u|%*d|\n", w, i, w, i, w, i);
        } else {
            printf("|%*o|%*u|%*d|\n", w, i, w, i, w, -j);
            j++;
        }
    }
    return 0;
}
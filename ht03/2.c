#include <stdio.h>
#include <stdlib.h>

enum { MAX_PERCENT = 100 };

struct Pair
{
    int value;
    int prob;
};

int
main(void)
{
    int n;
    scanf("%d", &n);
    
    struct Pair *pairs = calloc(n, sizeof(*pairs));
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &pairs[i].value, &pairs[i].prob);
    }
    
    int m, seed;
    scanf("%d%d", &m, &seed);
    srand(seed);
    for (int i = 0; i < m; i++) {
        int a = rand() / (RAND_MAX + 1.0) * MAX_PERCENT;
        int low = 0;
        for (int j = 0; j < n; j++) {
            if (a >= low && a < low + pairs[j].prob) {
                printf("%d\n", pairs[j].value);
                break;
            }
            low += pairs[j].prob;
        }
    }
    free(pairs);
    return 0;
}

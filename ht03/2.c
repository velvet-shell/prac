#include <stdio.h>
#include <stdlib.h>

enum { MAX_PERCENT = 100 };

int
main(void)
{
    int n;
    scanf("%d", &n);
   
    int prob[100];
    int last = 0;
    for (int i = 0; i < n; i++) {
        int value, index;
        scanf("%d%d", &value, &index);
        if (index > 100 || last + index > 100) {
            return 1;
        }
        for (int j = last; j < last + index; j++) {
            prob[j] = value;
        }
        last += index;
    }
    
    int m, seed;
    scanf("%d%d", &m, &seed);
    srand(seed);
    for (int i = 0; i < m; i++) {
        int a = rand() / (RAND_MAX + 1.0) * MAX_PERCENT;
        printf("%d\n", prob[a]);
    }
    return 0;
}

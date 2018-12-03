#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char* argv[])
{
    if (argc != 5) {
        return 1;
    }
    int count = atoi(argv[1]);
    int low = atoi(argv[2]);
    int high = atoi(argv[3]);
    int seed = atoi(argv[4]);
    
    srand(seed);
    for (int i = 0; i < count; i++) {
        int a = rand() / (RAND_MAX + 1.0) * (high - low);
        a += low;
        printf("%d\n", a);
    }
    return 0;
}

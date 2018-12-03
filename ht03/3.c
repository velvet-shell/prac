#include <stdlib.h>
#include <stdio.h>

enum
{
    MULTIPLIER = 1103515245,
    INCREMENT = 12345,
    MODULE = 2147483648  
};

struct RandomOperations;

typedef struct RandomGenerator
{
    struct RandomOperations *ops;
    int current;
} RandomGenerator;

void destroy(RandomGenerator *rr) {
    free(rr);
    return;
}

int next(RandomGenerator *rr) {
    rr->current = ((unsigned)rr->current * MULTIPLIER + INCREMENT) % MODULE;
    return rr->current;
}

typedef struct RandomOperations
{
    void (*destroy)(RandomGenerator *);
    int (*next)(RandomGenerator *);
} RandomOperations;

RandomOperations operations = {destroy, next};

RandomGenerator *random_create(int seed)
{
    RandomGenerator *rr = calloc(1, sizeof(*rr));
    rr->ops = &operations;
    rr->current = seed;
    return rr;
}

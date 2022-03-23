#ifndef BIG_INT_H
#define BIG_INT_H

#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BigInt BigInt;

struct BigInt{
    char *number;
    size_t number_lengh;
    bool positive;
    void (*print)(BigInt *self);
};

BigInt *create_bigint();
BigInt *construct(long long number);
BigInt *construct_from_bigint(BigInt *bigint);
void free_big_int(BigInt *bigint);

#endif /* BIG_INT_H */